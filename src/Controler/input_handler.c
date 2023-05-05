//
// Created by Axel PETIT on 28/04/2023.
//
#include "input_handler.h"
#include <printf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void get_status(aquarium *a) {
  // Check if the connexion is valid
  printf("-> OK : Connecté au contrôleur, %d  poisson(s) trouvé(s)\n",
         a->nb_fish);
  // Return list of fishes
  for (int i = 0; i < a->nb_fish; i++) {
    show_fish(a->fishes[i]);
  }
}

int client_add_fish(aquarium *a, char argv[], int argc) {
  // get arguments
  char input[100] = "";
  char *fish_name = malloc(sizeof(char) * 20);
  long int long_x = -1, long_y = -1, view_width = -1, view_height = -1;
  char mobility_name[20] = "";
  sscanf(argv, "%s %s at %ldx%ld %ldx%ld %s", input, fish_name, &long_x,
         &long_y, &view_width, &view_height, mobility_name);

  // Check if the fish is valid
  if ((strcmp(fish_name, "") == 0) || long_x == -1 || long_y == -1 ||
      view_width == -1 || view_height == -1 ||
      (strcmp(mobility_name, "") == 0)) {
    printf("Error: fish parameters are not valid\n");
    return -1;
  }
  // Check if the mobility is valid
  if (strcmp(mobility_name, "") == 0) {
    printf("Error: Unknown mobility\n");
    return -1;
  }
  // Check if the fish is already in the aquarium
  for (int i = 0; i < a->nb_fish; i++) {
    if (strcmp(a->fishes[i]->name, fish_name) == 0) {
      printf("Error: fish %s already in the aquarium\n", fish_name);
      return -1;
    }
  }

  int x = (int)long_x;
  int y = (int)long_y;
  fish *f = init_basic_fish(fish_name, x, y, mobility_name);
  add_fish(a, f);

  printf("OK\n");
  return 0;
}

int client_del_fish(aquarium *a, char argv[], int argc) {
  // get arguments
  char input[100] = "";
  char fish_name[20] = "";
  sscanf(argv, "%s %s", input, fish_name);

  // Check if the fish is valid
  if (strcmp(fish_name, "") == 0) {
    printf("Error: fish name must be specified\n");
    return -1;
  }
  // Check if the fish is already in the aquarium and delete it.
  int fish_found = 0;
  for (int i = 0; i < a->nb_fish; i++) {
    if (strcmp(a->fishes[i]->name, fish_name) == 0) {
      fish_found = 1;
      delete_fish(a, a->fishes[i]);
      printf("OK\n");
    }
  }
  if (fish_found == 0) {
    printf("Error: fish %s not found\n", fish_name);
    return -1;
  }
  return 0;
}

void client_get_fishes(aquarium *a, char argv[], int argc) {

  if (a->nb_fish == 0) {
    printf("No fish in the aquarium\n");
  }

  printf("list\n");
  for (int i = 0; i < a->nb_fish; i++) {
    show_fish(a->fishes[i]);
  }
}

void client_start_fish(aquarium *a, char argv[], int argc) {
  // get arguments
  char input[100] = "";
  char fish_name[20] = "";
  sscanf(argv, "%s %s", input, fish_name);

  // Check if the fish is valid
  if (strcmp(fish_name, "") == 0) {
    printf("Error: fish name must be specified\n");
    return;
  }
  // Check if the fish is already in the aquarium and start it.
  int fish_found = 0;
  for (int i = 0; i < a->nb_fish; i++) {
    if (strcmp(a->fishes[i]->name, fish_name) == 0) {
      fish_found = 1;
      if (a->fishes[i]->is_started == 1) {
        printf("Error: fish %s already started\n", fish_name);
        return;
      }
      a->fishes[i]->is_started = 1;
      printf("OK\n");
    }
  }
  if (fish_found == 0) {
    printf("Error: fish %s not found\n", fish_name);
    return;
  }
}

void client_welcome(aquarium *a, char argv[], int argc) {
  // if no view ID in argument, attribute random available view

  // attribute available view given in parameter
}

int client_quit(aquarium *a, char argv[], int argc) {
  // get arguments
  char input[100] = "";
  char option[20] = "";
  char extra_argument[100] = "";
  sscanf(argv, "%s %s %s", input, option, extra_argument);
  if (strcmp(extra_argument, "") != 0) {
    printf("Error: too many arguments\n");
    return -1;
  }
  if (strcmp(option, "out") == 0) {
    printf("bye\n");
    exit(0);
  }
  printf("Invalid option\n");
  return -1;
}

void client_ping(aquarium *a, char argv[], int argc) { printf("pong\n"); }

void handler_load(aquarium *a, char argv[], int argc) {
  // get arguments
  char input[100] = "";
  char aquarium_file[20] = "";
  char extra_argument[100] = "";
  sscanf(argv, "%s %s %s", input, aquarium_file, extra_argument);

  if (strcmp(extra_argument, "") != 0) {
    printf("Error: too many arguments\n");
    return;
  }

  if (strcmp(aquarium_file, "") == 0) {
    printf("Error: aquarium file must be specified\n");
    return;
  }
  init_aquarium_from_file(a, aquarium_file);
  if (a == NULL) {
    printf("Error: aquarium file not found\n");
    return;
  }
  printf("-> aquarium loaded (%d display view) !\n", a->nb_view);
}

void handler_show(aquarium *a, char argv[], int argc) {
  if (a == NULL) {
    printf("Error: no aquarium loaded\n");
    return;
  }
  show_aquarium(a);
}
