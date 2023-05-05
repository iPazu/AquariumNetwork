//
// Created by Axel PETIT on 28/04/2023.
//

#ifndef AQUARIUM_NETWORK_INPUT_HANDLER_H
#define AQUARIUM_NETWORK_INPUT_HANDLER_H

#include "../Modele/aquarium.h"

void get_status(aquarium *a);

int client_add_fish(aquarium *a, char argv[], __attribute__((unused)) int argc);

int client_del_fish(aquarium *a, char argv[], __attribute__((unused)) int argc);

void client_get_fishes(aquarium *a, __attribute__((unused)) char argv[], __attribute__((unused)) int argc);

void client_start_fish(aquarium *a, char argv[], __attribute__((unused)) int argc);

void ls(aquarium *a);

void client_add_view(aquarium *a, char argv[], int argc);

void client_del_view(aquarium *a, char argv[], int argc);

void client_show_aquarium(aquarium *a, char argv[], int argc);

void client_save_aquarium(aquarium *a, char argv[], int argc);

void client_welcome(__attribute__((unused)) aquarium *a, __attribute__((unused)) char argv[], __attribute__((unused)) int argc);

int client_quit(__attribute__((unused)) aquarium *a, char argv[], __attribute__((unused)) int argc);

void client_ping(__attribute__((unused)) aquarium *a, __attribute__((unused)) char argv[], __attribute__((unused)) int argc);

void handler_load(aquarium *a, char argv[], __attribute__((unused)) int argc);

void handler_show(aquarium *a, __attribute__((unused)) char argv[], __attribute__((unused)) int argc);

#endif // AQUARIUM_NETWORK_INPUT_HANDLER_H
