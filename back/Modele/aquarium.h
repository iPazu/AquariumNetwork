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

/**
 * @brief Initialize an aquarium
 * @param a
 * @param x_max
 * @param y_max
 * @param nb_fish
 * @param fishes
 */
void init_aquarium(aquarium *a, int x_max, int y_max, int nb_fish, fish *fishes[MAX_FISH]);

/**
 * @brief Add a fish to the aquarium
 * @param a
 * @param f
 */
void add_fish(aquarium *a, fish *f);

/**
 * @brief Move all the fishes in the aquarium
 * @param a
 */
void move_fishes(aquarium *a);

/**
 * @brief Delete a fish from the aquarium
 * @param a
 */
void delete_fish(aquarium *a, fish *f);

#endif //AQUARIUM_NETWORK_AQUARIUM_H
