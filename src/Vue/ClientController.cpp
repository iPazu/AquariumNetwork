#include "include/ClientController.hpp"
#include "include/ResponseHandler.hpp"

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>
#include "include/Console.hpp"

#define TIMEOUT_SECONDS 10
ClientController::ClientController(Console& console)
        : console(console), m_sockfd(-1), m_connected(false), responseHandler(console)
{
    worker = std::thread([this] {
        std::string command;
        while (true) {
            // Wait for a command
            {
                std::unique_lock<std::mutex> lock(mtx);
                cv.wait(lock, [this]{ return !commands.empty(); });

                // Get the next command
                command = commands.front();
                printf("Sending command: %s\n", command.c_str());
                commands.pop();
            }

            // Process the command
            send(command);
            char buffer[4096];

            std::cout << "Waiting for response..." << std::endl;
            receive(buffer, sizeof(buffer));

            std::memset(buffer, 0, sizeof(buffer));


        }
    });
}

ClientController::~ClientController() {
    // TODO: notify the worker thread to exit
    worker.join();
    disconnect();
}

void ClientController::addCommand(const std::string& command, const std::vector<std::string>& args) {
    std::lock_guard<std::mutex> lock(mtx);
    std::string fullCommand = command;
    for (const auto& arg : args) {
        fullCommand += " " + arg;
    }
    commands.push(fullCommand);
    cv.notify_one();
}


connectionVerif ClientController::connect(const std::string& ip, int port, std::ostream& out) {

    out << " ----- Connecting to server  ------\n";
    out << "Server address: " << ip << std::endl;
    out << "Server port: " << port << std::endl;


    // Create a socket
    m_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (m_sockfd < 0) {
        std::cerr << "Error creating socket\n";
        return connectionVerif(false, out);
    }

    // Resolve the server address
    struct hostent* server = gethostbyname(ip.c_str());

    if (server == nullptr) {
        std::cerr << "Error resolving server address\n";
        close(m_sockfd);
        m_sockfd = -1;
        return connectionVerif(false, out);
    }

    // Set up the server address
    struct sockaddr_in server_address{};
    bzero((char *) &server_address, sizeof(server_address));
    server_address.sin_family = AF_INET;
    bcopy((char *) server->h_addr, (char *)&server_address.sin_addr.s_addr, server->h_length);
    server_address.sin_port = htons(port);

    // Connect to the server
    if (::connect(m_sockfd, (struct sockaddr *) &server_address, sizeof(server_address)) < 0) {
        std::cerr << "Error connecting to server\n";
        close(m_sockfd);
        m_sockfd = -1;
        return connectionVerif(false, out);
    }
    m_connected = true;

    out << "Successfully connected to server\n";
    out <<  "----------------------------------\n";

    return connectionVerif(true, out);
}

void ClientController::disconnect() {
    if (m_connected) {
        close(m_sockfd);
        m_sockfd = -1;
        m_connected = false;
    }
}

int ClientController::send(const char* data, int len) {

    if (!m_connected) {
        std::cerr << "Error: not connected\n";
        return -1;
    }
    printf("Sending data: %s\n", data);
    int bytes_sent = ::send(m_sockfd, data, len, 0);
    if (bytes_sent < 0) {
        std::cerr << "Error sending data\n";
        disconnect();
    }

    return bytes_sent;
}

int ClientController::send(std::string data)
{
    return send(data.c_str(), data.length());
}

int ClientController::receive(char* buffer, int len) {
    if (!m_connected) {
        std::cerr << "Error: not connected\n";
        return -1;
    }

    // Set timeout for receiving
    struct timeval tv;
    tv.tv_sec = TIMEOUT_SECONDS;  // Set the timeout (in seconds)
    tv.tv_usec = 0;  // 0 microseconds

    if (setsockopt(m_sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) < 0) {
        std::cerr << "Error setting socket options: " << strerror(errno) << "\n";
        return -1;
    }

    int bytes_received = ::recv(m_sockfd, buffer, len, 0);
    if (bytes_received < 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            std::cerr << "Receive operation timed out\n";
            console.println("Receive operation timed out\n");
            disconnect();
        } else {
            std::cerr << "Error receiving data: " << strerror(errno) << "\n";
        }
        return -1;
    }
    std::string responseStr(buffer);
    std::cout << "Received response: " << responseStr << std::endl;
    responseHandler.processResponse(responseStr);

    return bytes_received;
}
int ClientController::receive(std::string& buffer)
{
    char buf[4098];
    receive(buf, 4098);
    auto bufSize = strlen(buf);
    for(auto i = 0; i < bufSize; ++i)
    {
        buffer += buf[i];
    }
    return 0;
}

bool ClientController::isConnected() const {
    return m_connected;
}
