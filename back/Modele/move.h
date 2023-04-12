//
// Created by Axel PETIT on 12/04/2023.
//

#ifndef AQUARIUM_NETWORK_MOVE_H
#define AQUARIUM_NETWORK_MOVE_H

#include "fish.h"

/**
 * @brief Move a fish randomly
 * @param fish
 * @param x_max_aquarium
 * @param y_max_aquarium
 */
void RandomPointWay(fish * fish, int x_max_aquarium, int y_max_aquarium);

/**
 * @brief Move a fish horizontally
 * @param fish
 * @param x_max_aquarium
 * @param y_max_aquarium
 */
void HorizontalWay(fish * fish, int x_max_aquarium, int y_max_aquarium);

/**
 * @brief Move a fish vertically
 * @param fish
 * @param x_max_aquarium
 * @param y_max_aquarium
 */
void VerticalWay(fish * fish, int x_max_aquarium, int y_max_aquarium);

#endif //AQUARIUM_NETWORK_MOVE_H
