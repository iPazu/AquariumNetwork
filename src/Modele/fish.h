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
    int strength;
    char* species;
    void (*move)(struct fish *, int x_max_aquarium, int y_max_aquarium);
    struct fish* (*reproduction)(struct fish *, struct fish *);
    struct fish* (*hunting)(struct fish *, struct fish *);
} fish;

/**
 * @brief Initialize a fish
 * @param f
 * @param name
 * @param x
 * @param y
 * @param speed
 * @param species
 * @param move_name
 */
fish *init_fish(char *name, int x, int y, int speed, int strength, char* species, char* move_name, char* behavior_name, char* hunting_name);

/**
 * @brief Move a fish
 * @param f
 * @param x_max_aquarium
 * @param y_max_aquarium
 */
void move_fish(fish *f, int x_max_aquarium, int y_max_aquarium);

void show_fish(fish *f);

#endif //AQUARIUM_NETWORK_FISH_H
