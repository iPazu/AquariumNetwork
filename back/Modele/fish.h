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

void init_fish(fish *f, char *name, int x, int y, int speed, char* move_name);

void move_fish(fish *f, int x_max_aquarium, int y_max_aquarium);

#endif //AQUARIUM_NETWORK_FISH_H
