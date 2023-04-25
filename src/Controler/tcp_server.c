#define MESSAGE_SIZE 2000

#include "tcp_server.h"

int clients_count = 0;
client_data *clients[MAX_CLIENTS] = {NULL};

void *client_handler(void *void_info) {

  client_data *info = (client_data *)void_info;
  int *sock = info->socket;
  int client_id = info->id;
  int read_size;
  char client_message[MESSAGE_SIZE];

  // Receive client message
  while ((read_size = recv(*sock, client_message, 2000, 0)) > 0) {

    // Send message back to client
    write(*sock, client_message, strlen(client_message));
    memset(client_message, 0, 2000);
  }

  // Check if client disconnected
  if (read_size == 0) {
    printf("Client disconnected\n");
    // Remove client from array
    clients[client_id] = NULL;
  } else if (read_size == -1) {
    perror("Receive failed");
  }

  // Close socket and free memory
  close(*sock);
  free(sock);
  free(info);

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
  while ((client_sock = accept(socket_desc, (struct sockaddr *)&client,
                               (socklen_t *)&c))) {
    puts("Connection accepted");

    // Create new thread for client connection
    new_sock = malloc(1);
    *new_sock = client_sock;

    // Add client socket to array
    /* int i;
    for (i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i] == 0) {
            clients[i] = client_sock;
            break;
        }
    } */
    if (clients_count < MAX_CLIENTS) {
      client_data *client = malloc(sizeof(client_data));
      client->id = clients_count;
      client->socket = new_sock;
      clients[clients_count] = client;
      clients_count++;

    } else {

      printf("Too many clients, connection rejected\n");
      continue;
    }

    if (pthread_create(&sniffer_thread, NULL, client_handler,
                       (void *)clients[clients_count]) < 0) {
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
