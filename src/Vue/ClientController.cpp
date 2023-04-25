#include "include/ClientController.hpp"
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

ClientController::ClientController() : m_sockfd(-1), m_connected(false) {}

ClientController::~ClientController() {
    disconnect();
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

    printf("Successfully connected to server\n");
    printf("----------------------------------\n");
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

    int bytes_sent = ::send(m_sockfd, data, len, 0);
    if (bytes_sent < 0) {
        std::cerr << "Error sending data\n";
        disconnect();
    }
    return bytes_sent;
}

int ClientController::receive(char* buffer, int len) {
    if (!m_connected) {
        std::cerr << "Error: not connected\n";
        return -1;
    }

    int bytes_received = ::recv(m_sockfd, buffer, len, 0);
    if (bytes_received < 0) {
        std::cerr << "Error receiving data\n";
        disconnect();
    }
    return bytes_received;
}

bool ClientController::isConnected() const {
    return m_connected;
}
