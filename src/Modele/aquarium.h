//
// Created by Axel PETIT on 12/04/2023.
//

#ifndef AQUARIUM_NETWORK_AQUARIUM_H
#define AQUARIUM_NETWORK_AQUARIUM_H

#define MAX_FISHES 100
#define MAX_VIEW 100

#include "fish.h"
#include "view.h"

typedef struct aquarium {
  int width;
  int height;
  int nb_fish;
  fish *fishes[MAX_FISHES];
  int nb_view;
  view *views[MAX_VIEW];
  int *id_available_views[MAX_VIEW];
} aquarium;

/**
 * @brief Initialize an aquarium
 * @param a
 * @param x_max
 * @param y_max
 * @param nb_fish
 * @param fishes
 */
aquarium *init_aquarium(int x_max, int y_max, int nb_fish, int nb_view);

/**
 * @brief Initialize an aquarium from a file
 * @param a
 * @param file_name
 */
void init_aquarium_from_file(aquarium *a, char *file_name);

/**
 * @brief Add a fish to the aquarium
 * @param a
 * @param f
 */
void add_fish(aquarium *a, fish *f);

/**
 * @brief Move all the fishes in the aquarium
 * @param a
 */
void move_fishes(aquarium *a);

/**
 * @brief Delete a fish from the aquarium
 * @param a
 */
void delete_fish(aquarium *a, fish *f);

/**
 * @brief Show the aquarium
 * @param a
 */
void show_aquarium(aquarium *a);

void show_aquarium_fishes(aquarium *a);

void add_view(aquarium *a, view *v);

void delete_view(aquarium *a, view *v);

void show_aquarium_views(aquarium *a);

int view_superposition(aquarium *a);

int *available_views(aquarium *a);

void save_aquarium(aquarium *a, char *file_name);

void free_aquarium(aquarium *a);

void fish_reproduction(aquarium *a);

#endif // AQUARIUM_NETWORK_AQUARIUM_H
