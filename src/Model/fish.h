#ifndef AQUARIUM_NETWORK_FISH_H
#define AQUARIUM_NETWORK_FISH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct fish {
  char *name;
  int x;
  int y;
  int width;
  int height;
  int speed;
  int strength;
  int gender;     // 0 = female, 1 = male
  int is_started; // 0 : not started, 1 : started
  char *species;
  void (*move)(struct fish *, int x_max_aquarium, int y_max_aquarium);
  struct fish *(*reproduction)(struct fish *, struct fish *);
  struct fish *(*hunting)(struct fish *, struct fish *);
} fish;

fish *init_fish(char *name, int x, int y, int speed, int strength, int gender,
                char *species, void (*move_function)(fish *, int, int),
                fish *(*reproduction_function)(fish *, fish *),
                fish *(*hunting_function)(fish *, fish *));

fish *init_fish_from_client(char *name, int x, int y, int speed, int strength,
                            int gender, char *species, char *move_name,
                            char *reproduction_name, char *hunting_name);

fish *init_basic_fish(char *name, int x, int y, int width, int height,
                      char *move_name);

void move_fish(fish *f, int x_max_aquarium, int y_max_aquarium);

fish *chose_random_init_fish(char *name, int x, int y, char *move_name);

void show_fish(fish *f, char *buf);

void show_fish_ls(fish *f, char *buf);

#endif // AQUARIUM_NETWORK_FISH_H
