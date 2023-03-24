#include <stdlib.h>
#include "fish.h"

int check_position(fish* f, int dx, int dy, int x_max, int y_max) {
    if ((0 < f->x + dx) && ( f->x + dx < x_max ) && (0 < f->y + dy) && (f->y + dy < y_max)) {
        return 1;
    }
    return 0;
}

void no_move(fish* f, int x_max_aquarium, int y_max_aquarium) {
}

void random_move(fish* f, int x_max_aquarium, int y_max_aquarium) {
    int dx;
    int dy;

    int inside = 0;
    while (!inside) {
        dx = (rand() % 1) * f->speed * f->dir_x;
        dy = (rand() % 1) * f->speed * f->dir_y;
        inside = check_position(f, dx, dy, x_max_aquarium, y_max_aquarium);
    }

    f->x += dx;
    f->y += dy;
    f->dir_x += rand()%1;
    f->dir_y += rand()%1;

}

void random_move_with_updated_speed(fish* f,  int x_max_aquarium, int y_max_aquarium) {
    random_move(f, x_max_aquarium, y_max_aquarium);
    int new_speed = rand()%1;
    f->speed = (rand()%1 == 0) ? new_speed : -new_speed;
}
