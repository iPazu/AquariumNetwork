#ifndef AQUARIUM_H
#define AQUARIUM_H

#define MAX_FISHES 100
#define AQUA_SIZE 100

#include "fish.h"
#include <stdlib.h>
#include <unistd.h>

typedef struct aquarium {
  int max_x;
  int max_y;
  fish *fishes[MAX_FISHES];
  char *name_fishes[MAX_FISHES];
  int nb_fishes;
} aquarium;

void aquarium_init(aquarium *a);
void aquarium_fill(aquarium *a, int nb_fishes);
void aquarium_add_fish(aquarium *a, fish *f);
void aquarium_delete_fish(aquarium *a, fish *f);
void aquarium_move_fishes(aquarium *a);

#endif
