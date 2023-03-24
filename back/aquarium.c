#include "aquarium.h"

void aquarium_init(aquarium *a){
    a->nb_fishes = 0;
    a->max_x = AQUA_SIZE;
    a->max_y = AQUA_SIZE;
}

void aquarium_add_fish(aquarium *a, fish *f){
    a->fishes[a->nb_fishes] = f;
    a->nb_fishes++;
}

fish *fish_init(void (*move)(fish *, int x_max_aquarium, int y_max_aquarium)){
    fish *f = malloc(sizeof(fish));
    f->x = 0;
    f->y = 0;
    f->move = move;
    f->speed = 1;
    f->dir_x = 1;
    f->dir_y = 1;
    return f;
}

void aquarium_fill(aquarium* a, int nb_fishes) {
    for (int i = 0; i < nb_fishes ; i++) {
        fish* f = fish_init(&no_move);
        a->fishes[i] = f;
    }
}

void aquarium_move_fishes(aquarium *a){
    int i;
    for(i = 0; i < a->nb_fishes; i++){
        fish* fish = a->fishes[i];
        fish->move(fish, a->max_x, a->max_y);
        sleep(1);
    }
}
