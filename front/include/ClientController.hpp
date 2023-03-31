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

using connectionVerif = std::pair<bool, std::ostream&>;

class ClientController {
public:
    ClientController();

    virtual ~ClientController();

    connectionVerif connect(const std::string &ip, int port, std::ostream& out = std::cout);

    void disconnect();

    int send(const char *data, int len);

    int receive(char *buffer, int len);

    bool isConnected() const;

private:
    int m_sockfd;
    bool m_connected;
};

#endif //AQUARIUMNETWORK_CLIENTCONTROLLER_H
