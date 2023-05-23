#include "tcp_server.h"
#include "../main.h"

aquarium *aqua;
int clients_count = 0;
client_data *clients[MAX_CLIENTS] = {NULL};

void *client_handler(void *void_info)
{
    client_data *info = (client_data *)void_info;
    int *sock = info->socket;
    int client_id = info->id;
    int view_id = -1;
    int read_size;
    char client_message[MESSAGE_SIZE];
    //printf("-- VIEWS INTERACTIONS --\n");
    disp_initial_available_views(aqua, sock, client_id, client_message);

    printf("-- LOOP --\n");
    // Receive client message
    while (running_status && ((read_size = recv(*sock, client_message, MESSAGE_SIZE, 0)) > 0))
    {
        printf("FROM CLIENT %d: %s\n", client_id, client_message);
        client_get_input(aqua, client_id, sock, client_message, &view_id);
        memset(client_message, 0, MESSAGE_SIZE);

    }

    // Check if client disconnected
    if (read_size == 0)
    {
        printf("Client disconnected\n");
        
        if (view_id != -1) aqua->views[view_id]->is_assigned = -1;
        // Remove client from array
        clients[client_id] = NULL;
        clients_count--;
    }
    else if (read_size == -1)
    {
        perror("Receive failed");

        if (view_id != -1) aqua->views[view_id]->is_assigned = -1;
        // Remove client from array
        clients[client_id] = NULL;
        clients_count--;
    }

    // Close socket and free memory
    close(*sock);
    free(sock);
    free(info);

    return 0;
}

int start_server(aquarium *a)
{

    aqua = a;
    int socket_desc, client_sock, c, *new_sock;
    struct sockaddr_in server, client;
    pthread_t sniffer_thread;

    // Create socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }

    // Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT_NUMBER);

    // Bind
    while (bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("Bind failed");
        sleep(1);
    }
    printf("Bind done\n");

    // Listen
    listen(socket_desc, 3);
    printf("Waiting for the first incoming connection...\n");

    // Accept incoming connections
    c = sizeof(struct sockaddr_in);
    while ((client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t *)&c)))
    {
        puts("Connection accepted");

        // Create new thread for client connection
        new_sock = malloc(1);
        *new_sock = client_sock;

        if (clients_count < MAX_CLIENTS)
        {
            client_data *client = malloc(sizeof(client_data));
            int c_id = 0;
            while (clients[c_id] != NULL)
            {
                c_id++;
            }
            client->id = c_id;
            client->socket = new_sock;
            clients[c_id] = client;
            clients_count++;
        }
        else
        {

            printf("Too many clients, connection rejected\n");
            continue;
        }

        printf("Client assigned to ID %d\n", clients_count - 1);

        if (pthread_create(&sniffer_thread, NULL, client_handler, (void *)clients[clients_count - 1]) < 0)
        {
            perror("Could not create thread");
            return 1;
        }

        printf("Handler assigned\n");
    }

    return 0;
}
