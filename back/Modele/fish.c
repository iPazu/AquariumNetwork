//
// Created by Axel PETIT on 12/04/2023.
//

#include <string.h>
#include <stdio.h>
#include "fish.h"
#include "move.h"


void *move_function(char *move_name) {
    if (strcmp(move_name, "RandomPointWay") == 0) {
        return RandomPointWay;
    }
    return RandomPointWay;
}


void init_fish(fish *f, char *name, int x, int y, int speed, char* move_name) {
    f->name = name;
    f->x = x;
    f->y = y;
    f->speed = speed;
    f->move = move_function(move_name);

    printf("Fish %s created\n", f->name);
}

