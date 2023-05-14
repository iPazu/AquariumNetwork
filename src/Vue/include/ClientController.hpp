//
// Created by Alex Laboirie on 24/03/2023.
//

#ifndef AQUARIUMNETWORK_CLIENTCONTROLLER_H
#define AQUARIUMNETWORK_CLIENTCONTROLLER_H


#include <string>
#include <fstream>
#include <iostream>
#include <utility>
#include <tuple>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

using connectionVerif = std::pair<bool, std::ostream&>;

class ClientController {
public:
    ClientController();

    virtual ~ClientController();

    connectionVerif connect(const std::string &ip, int port, std::ostream& out = std::cout);

    void disconnect();

    void addCommand(const std::string& command);

    int send(const char *data, int len);
    int send(std::string);

    int receive(char *buffer, int len);
    int receive(std::string&);

    bool isConnected() const;

private:
    int m_sockfd;
    bool m_connected;
    std::queue<std::string> commands; // Queue of commands
    std::mutex mtx; // Mutex for synchronizing access to the queue
    std::condition_variable cv; // Condition variable for notifying the thread of new commands
    std::thread worker; // Worker thread
};

#endif //AQUARIUMNETWORK_CLIENTCONTROLLER_H
