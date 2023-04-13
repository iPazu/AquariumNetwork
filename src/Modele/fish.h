//
// Created by Axel PETIT on 12/04/2023.
//

#ifndef AQUARIUM_NETWORK_FISH_H
#define AQUARIUM_NETWORK_FISH_H

typedef struct fish {
    char *name;
    int x;
    int y;
    int speed;
    void (*move)(struct fish *, int x_max_aquarium, int y_max_aquarium);
} fish;

/**
 * @brief Initialize a fish
 * @param f
 * @param name
 * @param x
 * @param y
 * @param speed
 * @param move_name
 */
void init_fish(fish *f, char *name, int x, int y, int speed, char* move_name);

/**
 * @brief Move a fish
 * @param f
 * @param x_max_aquarium
 * @param y_max_aquarium
 */
void move_fish(fish *f, int x_max_aquarium, int y_max_aquarium);

#endif //AQUARIUM_NETWORK_FISH_H
