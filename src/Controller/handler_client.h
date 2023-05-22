#ifndef AQUARIUM_NETWORK_HANDLER_CLIENT_H
#define AQUARIUM_NETWORK_HANDLER_CLIENT_H

#include "../Model/aquarium.h"

void client_get_input(aquarium *a, int client_id, int *socket, char *client_message, int *view_id);

void client_status(aquarium *a, int client_id, int *socket, int *view_id);

int client_add_fish(aquarium *a, char argv[], int client_id, int *socket, int *view_id);

int client_del_fish(aquarium *a, char argv[], int client_id, int *socket);

void client_start_fish(aquarium *a, char argv[], int client_id, int *socket);

int client_quit(char argv[], int client_id, int *socket);

void client_welcome(aquarium *a, char argv[], int client_id, int *socket, int *view_id);

void client_get_fishes(aquarium *a, int client_id, int *socket);

void client_ls(aquarium *a, int client_id, int *socket);

void client_get_fishes_continuously(aquarium *a, int client_id, int *socket);

void client_ping(char argv[], int client_id, int *socket);

void views_interaction(aquarium *aqua, int *sock, int client_id,
                       char *client_message);

#endif //AQUARIUM_NETWORK_HANDLER_CLIENT_H