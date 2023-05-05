//
// Created by Axel PETIT on 02/05/2023.
//

#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <netinet/in.h>
#include <stdlib.h>
#include "server.h"

void *handle_connection(void *socket_desc) {
    int client_socket = *(int *) socket_desc;
    char client_message[2000];
    int n;

    while ((n = recv(client_socket, client_message, sizeof(client_message), 0)) > 0) {
        client_message[n] = '\0';
        printf("Client message: %s\n", client_message);
        send(client_socket, client_message, strlen(client_message), 0);
    }

    close(client_socket);
    pthread_exit(NULL);
}


int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    pthread_t threads[10];
    int i = 0;

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT_NUMBER);

    if (bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, 10) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    while (1) {
        socklen_t client_address_length = sizeof(client_address);
    }
}