#include "aquarium.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void fish_random_move(fish *f) {
  f->x += (rand() % 1) * f->speed;
  f->y += (rand() % 1) * f->speed;
  int msleep(unsigned int tms) { return usleep(tms * 1000); }

  void aquarium_init(aquarium * a) {
    a->nb_fishes = 0;
    a->max_x = AQUA_SIZE;
    a->max_y = AQUA_SIZE;
  }

  void aquarium_add_fish(aquarium * a, fish * f) {
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

  void aquarium_move_fishes(aquarium * a) {
    int i;
    for (i = 0; i < a->nb_fishes; i++) {
      fish_random_move(a->fishes[i]);
      sleep(1);
    }
  }

  void aquarium_fill(aquarium * a, int nb_fishes) {
    for (int i = 0; i < nb_fishes; i++) {
      char *first_name = "Nemo";
      char last_name[2];
      int full_name_size = strlen(first_name) + 1 + strlen(last_name) + 1;
      char *full_name = (char *)malloc(full_name_size);
      strcpy(full_name, first_name);
      strcat(full_name, " ");
      sprintf(last_name, "%d", i);
      strcat(full_name, last_name);

      fish *f = fish_init(full_name, &random_move_with_updated_speed);
      aquarium_add_fish(a, f);
      print_fish(f);
    }
  }

  void aquarium_move_fishes(aquarium * a) {
    int i;
    for (i = 0; i < a->nb_fishes; i++) {
      fish *fish = a->fishes[i];
      fish->move(fish, a->max_x, a->max_y);
      msleep(20);
      print_fish(fish);
    }
  }

  // int main() {
  //     aquarium* a = malloc(sizeof(aquarium));
  //     aquarium_init(a);
  //     aquarium_fill(a, 10);
  //     aquarium_move_fishes(a);
  //     aquarium_move_fishes(a);
  //     return 0;
  // }
