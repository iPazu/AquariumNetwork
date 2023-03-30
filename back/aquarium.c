#include "aquarium.h"

void fish_random_move(fish *f) {
  f->x += (rand() % 1) * f->speed;
  f->y += (rand() % 1) * f->speed;
}

void aquarium_init(aquarium *a) {
  a->nb_fishes = 0;
  a->max_x = AQUA_SIZE;
  a->max_y = AQUA_SIZE;
}

void aquarium_add_fish(aquarium *a, fish *f) {
  a->fishes[a->nb_fishes] = f;
  a->nb_fishes++;
}

fish *fish_init() {
  fish *f = malloc(sizeof(fish));
  f->x = 0;
  f->y = 0;
  f->speed = 1;
  return f;
}

void aquarium_move_fishes(aquarium *a) {
  int i;
  for (i = 0; i < a->nb_fishes; i++) {
    fish_random_move(a->fishes[i]);
    sleep(1);
  }
}