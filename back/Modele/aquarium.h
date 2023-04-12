//
// Created by Axel PETIT on 12/04/2023.
//

#ifndef AQUARIUM_NETWORK_AQUARIUM_H
#define AQUARIUM_NETWORK_AQUARIUM_H

#define MAX_FISH 100

#include "fish.h"

typedef struct aquarium {
    int x_max;
    int y_max;
    int nb_fish;
    fish *fishes[MAX_FISH];
} aquarium;

void init_aquarium(aquarium *a, int x_max, int y_max, int nb_fish, fish *fishes[MAX_FISH]);

void add_fish(aquarium *a, fish *f);

void move_fishes(aquarium *a);

#endif //AQUARIUM_NETWORK_AQUARIUM_H
