#include "tcp_server.h"

int clients[MAX_CLIENTS] = { 0 };

void *client_handler(void *socket_desc) {

    int sock = *(int *)socket_desc;
    int read_size;
    char client_message[2000];
    int client_number;

    // Receive client message
    while ((read_size = recv(sock, client_message, 2000, 0)) > 0) {

        // Send message back to client        
        write(sock, client_message, strlen(client_message));
        memset(client_message, 0, 2000);
    }

    // Check if client disconnected
    if (read_size == 0) {
        printf("Client disconnected\n");

        // Remove client from array
        int i;
        for (i = 0; i < MAX_CLIENTS; i++) {
            if (clients[i] == sock) {
                clients[i] = 0;
                break;
            }
        }
    }
    else if (read_size == -1) {
        perror("Receive failed");
    }

    // Close socket and free memory
    close(sock);
    free(socket_desc);

    return 0;
}

int start_server() {

    int socket_desc, client_sock, c, *new_sock;
    struct sockaddr_in server, client;
    pthread_t sniffer_thread;

    // Create socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1) {
        printf("Could not create socket");
    }

    // Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT_NUMBER);

    // Bind
    if (bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Bind failed");
        return 1;
    }
    printf("Bind done\n");

    // Listen
    listen(socket_desc, 3);
    printf("Waiting for the first incoming connection...\n");
    
    // Accept incoming connections
    c = sizeof(struct sockaddr_in);
    while ((client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t *)&c))) {
        puts("Connection accepted");

        // Create new thread for client connection
        new_sock = malloc(1);
        *new_sock = client_sock;

        // Add client socket to array
        int i;
        for (i = 0; i < MAX_CLIENTS; i++) {
            if (clients[i] == 0) {
                clients[i] = client_sock;
                break;
            }
        }

        if (i == MAX_CLIENTS) {
            printf("Too many clients, connection rejected\n");
            continue;
        }

        if (pthread_create(&sniffer_thread, NULL, client_handler, (void *)new_sock) < 0) {
            perror("Could not create thread");
            return 1;
        }

        printf("Handler assigned\n");
    }

    if (client_sock < 0) {
        perror("Accept failed");
        return 1;
    }

    return 0;
}
