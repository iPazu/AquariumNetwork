#ifndef TCP_SERVER_H
#define TCP_SERVER_H


#include "handler_server.h"
#include "handler_client.h"

#define MAX_CLIENTS 10
#define PORT_NUMBER 3000

typedef struct client_data {
    int id;
    int *socket;
} client_data;


int start_server(aquarium *a);

/**
 * @brief Client connection handler that will be called in a thread for each client
 * 
 * Pour le moment, le serveur ne fait que recevoir et renvoyer le message du client
 * 
 * @param socket_desc The client socket descriptor
 * @return void* 
 */
void *client_handler(void *);

#endif