#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

#define MAX_CLIENTS 10
#define PORT_NUMBER 3000

typedef struct client_data {
    int id;
    int *socket;
} client_data;

/**
 * @brief Start tcp_server
 * 
 * @return int error code
 */
int start_server();

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