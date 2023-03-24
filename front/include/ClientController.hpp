//
// Created by Alex Laboirie on 24/03/2023.
//

#ifndef AQUARIUMNETWORK_CLIENTCONTROLLER_H
#define AQUARIUMNETWORK_CLIENTCONTROLLER_H


#include <string>

class ClientController {
public:
    ClientController();

    virtual ~ClientController();

    bool connect(const std::string &ip, int port);

    void disconnect();

    int send(const char *data, int len);

    int receive(char *buffer, int len);

    bool isConnected() const;

private:
    int m_sockfd;
    bool m_connected;
};

#endif //AQUARIUMNETWORK_CLIENTCONTROLLER_H
