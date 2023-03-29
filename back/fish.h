#ifndef AQUARIUMNETWORK_FISH_H
#define AQUARIUMNETWORK_FISH_H

#endif //AQUARIUMNETWORK_FISH_H


typedef struct fish fish;

struct fish
{
    char* name;
    int x;
    int y;
    void (*move)(fish *, int x_max_aquarium, int y_max_aquarium);
    int speed;
    int dir_x;
    int dir_y;
};

void no_move(fish*, int x_max_aquarium, int y_max_aquarium);

void random_move(fish*, int x_max_aquarium, int y_max_aquarium);

void random_move_with_updated_speed(fish *, int x_max_aquarium, int y_max_aquarium);

void print_fish(fish*);

fish *fish_init(char* name, void (*move)(fish *, int x_max_aquarium, int y_max_aquarium));