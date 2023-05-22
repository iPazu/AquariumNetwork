#ifndef AQUARIUM_NETWORK_INPUT_HANDLER_H
#define AQUARIUM_NETWORK_INPUT_HANDLER_H

#include "../Model/aquarium.h"
#include "../Model/view.h"
#include <arpa/inet.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define MESSAGE_SIZE 4000




void client_get_fishes(aquarium *a, int client_id, int *socket);

void client_get_fishes_continuously(aquarium *a, int client_id, int *socket);

void client_ls(aquarium *a, int client_id, int *socket);

void client_add_view(aquarium *a, char argv[], int argc);

void client_del_view(aquarium *a, char argv[], int argc);

void client_show_aquarium(aquarium *a, char argv[], int argc);

void client_save_aquarium(aquarium *a, char argv[], int argc);

void client_welcome(aquarium *a, char argv[], int client_id, int *socket, int *view_id);

int client_quit(char argv[], int client_id, int *socket);

void client_ping(char argv[], int client_id, int *socket);

void server_load(aquarium *a, char argv[]);

void handler_show(aquarium *a);

void handler_save(aquarium *a);

void views_interaction(aquarium *aqua, int *sock, int client_id,
                       char *client_message);

#endif // AQUARIUM_NETWORK_INPUT_HANDLER_H