#include "fish.h"
#include <stdio.h>
#include <stdlib.h>

int check_position(fish *f, int dx, int dy, int x_max, int y_max) {
  if ((0 <= f->x + dx) && (f->x + dx <= x_max) && (0 <= f->y + dy) &&
      (f->y + dy <= y_max)) {
    return 1;
  }
  return 0;
}

void no_move(fish *f, int x_max_aquarium, int y_max_aquarium) {}

void random_move(fish *f, int x_max_aquarium, int y_max_aquarium) {
  int dx;
  int dy;

  int inside = 0;
  while (!inside) {
    dx = (rand() % 2) * f->speed * f->dir_x;
    dy = (rand() % 2) * f->speed * f->dir_y;
    inside = check_position(f, dx, dy, x_max_aquarium, y_max_aquarium);
  }

  f->x += dx;
  f->y += dy;
  f->dir_x += rand() % 2 > 0 ? 1 : -1;
  f->dir_y += rand() % 2 > 0 ? 1 : -1;
}

void random_move_with_updated_speed(fish *f, int x_max_aquarium,
                                    int y_max_aquarium) {
  random_move(f, x_max_aquarium, y_max_aquarium);

  int new_speed = rand() % 2 > 0 ? 1 : -1;
  if (f->speed + new_speed > 0) {
    f->speed += new_speed;
  }
}

void print_fish(fish *f) {
  printf("[%s at (%d, %d)], current speed : %d\n", f->name, f->x, f->y,
         f->speed);
}

fish *fish_init(char *name,
                void (*move)(fish *, int x_max_aquarium, int y_max_aquarium)) {
  fish *f = malloc(sizeof(fish));
  f->name = name;
  f->x = 0;
  f->y = 0;
  f->move = move;
  f->speed = 1;
  f->dir_x = 1;
  f->dir_y = 1;
  return f;
}