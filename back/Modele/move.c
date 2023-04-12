//
// Created by Axel PETIT on 12/04/2023.
//

#include <stdlib.h>
#include "move.h"


int check_position(int x, int y, int x_max, int y_max) {
    if (x < 0 || x > x_max || y < 0 || y > y_max) {
        return 0;
    }
    return 1;
}

void RandomPointWay(fish *f, int x_max_aquarium, int y_max_aquarium) {
    int x, y;
    do {
        x = rand() % (2 * f->speed);
        x = x - x / 2;
        y = rand() % (2 * f->speed);
        y = y - y / 2;
    } while (check_position(f->x + x, f->y + y, x_max_aquarium, y_max_aquarium) == 0);

    f->x = f->x + x;
    f->y = f->y + y;
}