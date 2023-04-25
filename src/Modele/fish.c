//
// Created by Axel PETIT on 12/04/2023.
//
#include "fish.h"
#include "behavior.h"
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

fish *(*get_reproduction_function(char *behavior_name))(fish *, fish *) {
  if (strcmp(behavior_name, "Classic") == 0) {
    return &classic_reproduction;
  }
  return &classic_reproduction;
}

fish *(*get_hunting_function(char *behavior_name))(fish *, fish *) {
  if (strcmp(behavior_name, "Classic") == 0) {
    return &classic_hunting;
  }
  return &classic_hunting;
}

fish *init_fish(char *name, int x, int y, int speed, int strength,
                char *species, char *move_name, char *reproduction_name,
                char *hunting_name) {
  fish *f = malloc(sizeof(fish));
  f->name = name;
  f->x = x;
  f->y = y;
  f->speed = speed;
  f->strength = strength;
  f->species = species;
  f->move = move_function(move_name);
  f->reproduction = get_reproduction_function(reproduction_name);
  f->hunting = get_hunting_function(hunting_name);

  return f;
}

void move_fish(fish *f, int x_max_aquarium, int y_max_aquarium) {
  f->move(f, x_max_aquarium, y_max_aquarium);
}

void show_fish(fish *f) { printf("[%s is at [%d, %d]\n", f->name, f->x, f->y); }
