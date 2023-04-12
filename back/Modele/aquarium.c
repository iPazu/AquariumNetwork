//
// Created by Axel PETIT on 12/04/2023.
//

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "aquarium.h"

void init_aquarium(aquarium *a, int x_max, int y_max, int nb_fish, fish *fishes[MAX_FISH]) {
    a->x_max = x_max;
    a->y_max = y_max;
    a->nb_fish = nb_fish;
}

void add_fish(aquarium *a, fish *f) {
    a->fishes[a->nb_fish] = f;
    a->nb_fish++;
    printf("Fish %s added, %d fish in the aquarium\n", f->name, a->nb_fish);
}

void move_fishes(aquarium *a) {
    for (int i = 0; i < a->nb_fish; i++) {
        a->fishes[i]->move(a->fishes[i], a->x_max, a->y_max);
        printf("Fish %s moved to %d, %d\n", a->fishes[i]->name, a->fishes[i]->x, a->fishes[i]->y);
    }
}

void delete_fish(aquarium *a, fish *f) {
    for (int i = 0; i < a->nb_fish; i++) {
        if (a->fishes[i] == f) {
            a->fishes[i] = a->fishes[a->nb_fish - 1];
            a->nb_fish--;
            break;
        }
    }
    printf("Fish %s deleted\n", f->name);
    free(f);
}

//int main() {
//    srand(time(NULL));
//
//    fish *f = malloc(sizeof(fish));
//    fish *f2 = malloc(sizeof(fish));
//    fish *f3 = malloc(sizeof(fish));
//    init_fish(f, "Nemo", 0, 0, 1, "RandomPointWay");
//    init_fish(f2, "Dory", 0, 0, 10, "RandomPointWay");
//    init_fish(f3, "Marlin", 0, 0, 1, "RandomPointWay");
//    aquarium *a = malloc(sizeof(aquarium));
//    init_aquarium(a, 10, 10, 0, NULL);
//    add_fish(a, f);
//    add_fish(a, f2);
//    move_fishes(a);
//    delete_fish(a, f);
//    move_fishes(a);
//    add_fish(a, f3);
//    move_fishes(a);
//    delete_fish(a, f2);
//    delete_fish(a, f3);
//
//    free(a);
//    return 0;
//}