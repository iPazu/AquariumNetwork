//
// Created by Axel PETIT on 28/04/2023.
//

#ifndef AQUARIUM_NETWORK_INPUT_HANDLER_H
#define AQUARIUM_NETWORK_INPUT_HANDLER_H

#include "../Modele/aquarium.h"

void get_status(aquarium *a);

int client_add_fish(aquarium *a, char argv[], int argc);

int client_del_fish(aquarium *a, char argv[], int argc);

#endif //AQUARIUM_NETWORK_INPUT_HANDLER_H
