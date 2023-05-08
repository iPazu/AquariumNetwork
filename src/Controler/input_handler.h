//
// Created by Axel PETIT on 28/04/2023.
//

#ifndef AQUARIUM_NETWORK_INPUT_HANDLER_H
#define AQUARIUM_NETWORK_INPUT_HANDLER_H

#include "../Modele/aquarium.h"

void get_status(aquarium *a);

int client_add_fish(aquarium *a, char argv[], int argc);

int client_del_fish(aquarium *a, char argv[], int argc);

void client_get_fishes(aquarium *a, char argv[], int argc);

void client_get_fishes_continuously(aquarium *a, char argv[], int argc);

void client_ls(aquarium *a, char argv[], int argc);

void client_start_fish(aquarium *a, char argv[], int argc);

void handler_add_view(aquarium *a, char argv[], int argc);

void handler_del_view(aquarium *a, char argv[], int argc);

void client_welcome(aquarium *a, char argv[], int argc);

int client_quit(aquarium *a, char argv[], int argc);

void client_ping(aquarium *a, char argv[], int argc);

void handler_load_aquarium(aquarium *a, char argv[], int argc);

void handler_show_aquarium(aquarium *a, char argv[], int argc);

#endif // AQUARIUM_NETWORK_INPUT_HANDLER_H
