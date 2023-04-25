//
// Created by Axel PETIT on 12/04/2023.
//

#include "fish.h"
#include "move.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *move_function(char *move_name) {
  if (strcmp(move_name, "RandomPointWay") == 0) {
    return RandomPointWay;
  }
  return RandomPointWay;
}

fish *init_fish(char *name, int x, int y, int speed, char *move_name) {
  fish *f = malloc(sizeof(fish));
  f->name = name;
  f->x = x;
  f->y = y;
  f->speed = speed;
  f->move = move_function(move_name);

  return f;
}

void move_fish(fish *f, int x_max_aquarium, int y_max_aquarium) {
  f->move(f, x_max_aquarium, y_max_aquarium);
}

void show_fish(fish *f) { printf("[%s is at [%d, %d]\n", f->name, f->x, f->y); }
