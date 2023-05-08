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
  long int long_x = -1, long_y = -1, long_width = -1, long_height = -1;
  char mobility_name[20] = "";
  sscanf(argv, "%s %s at %ldx%ld, %ldx%ld, %s", input, fish_name, &long_x,
         &long_y, &long_width, &long_height, mobility_name);

  // Check if the fish is valid
  if ((strcmp(fish_name, "") == 0) || long_x == -1 || long_y == -1 ||
      long_width == -1 || long_height == -1 ||
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
  int width = (int)long_width;
  int height = (int)long_height;
  fish *f = init_basic_fish(fish_name, x, y, width, height, mobility_name);
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
    printf("NOK : %s inexistant\n", fish_name);
    return -1;
  }
  return 0;
}

void client_start_fish(aquarium *a, char argv[], int argc) {
  // get arguments
  char input[100] = "";
  char fish_name[20] = "";
  sscanf(argv, "%s %s", input, fish_name);

  // Check that the fish is valid
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
  char input[100] = "";
  char as[20] = "";
  char in[100] = "";
  char id[100] = "";

  sscanf(argv, "%s %s %s %s", input, in, as, id);
  if (strcmp(as, "") == 0 && strcmp(in, "") == 0 && strcmp(id, "") == 0) {
    available_views(a);
    // choosing a random id
    int random_view = a->id_available_views[rand() % a->nb_available_views];
    printf("random view %d\n", random_view);
    return;
    // attribute available view given in parameter
  } else if (strcmp(in, "in") == 0 && strcmp(as, "as") == 0 &&
             strcmp(id, "") != 0) {

    // check if the view exists

    // check if the view is available
    if (!a->views[atoi(id)]->is_assigned) {
      a->views[atoi(id)]->is_assigned = 1;
      printf("greeting %d\n", atoi(id));
    }
    // the view is unavailable
    else {
      printf("no greeting\n");
    }

  } else if (strcmp(in, "in") != 0 || strcmp(as, "as") == 0) {
    printf("bad syntax, try again\n");

  } else {
    printf("frero fais un effort\n");
  }
}

void client_get_fishes(aquarium *a, char argv[], int argc) {

  if (a->nb_fish == 0) {
    printf("No fish in the aquarium\n");
    return;
  }

  printf("list\n");
  for (int i = 0; i < a->nb_fish; i++) {
    show_fish_ls(a->fishes[i]);
  }
}

void client_ls(aquarium *a, char argv[], int argc) {

  if (a->nb_fish == 0) {
    printf("No fish in the aquarium\n");
    return;
  }

  printf("list\n");
  for (int i = 0; i < a->nb_fish; i++) {
    show_fish_ls(a->fishes[i]);
  }
}

void client_get_fishes_continuously(aquarium *a, char argv[], int argc) {

  if (a->nb_fish == 0) {
    printf("No fish in the aquarium\n");
    return;
  }

  printf("list\n");
  for (int i = 0; i < a->nb_fish; i++) {
    show_fish_ls(a->fishes[i]);
  }
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

void handler_load_aquarium(aquarium *a, char argv[], int argc) {
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

void handler_show_aquarium(aquarium *a, char argv[], int argc) {
  char input[100] = "";
  char aquarium[100] = "";
  sscanf(argv, "%s %s", input, aquarium);
  printf("%s", input);
  if (strcmp(aquarium, "aquarium\0") != 0) {
    printf("aquarium argument must be specified");
  } else {
    show_aquarium(a);
    show_aquarium_views(a);
  }
}

void handler_add_view(aquarium *a, char argv[], int argc) {
  // get arguments
  char input[100] = "";
  char view[100] = "";
  long int view_id = -1;
  long int long_vue_x = -1, long_vue_y = -1, long_width = -1, long_height = -1;
  sscanf(argv, "%s %s %ld %ldx%ld+%ld+%ld", input, view, &view_id, &long_vue_x,
         &long_vue_y, &long_width, &long_height);

  // check the arguments

  // check that the view fits into the aquarium

  printf("-> view added\n");
}

void handler_del_view(aquarium *a, char argv[], int argc) {
  // get arguments
  char input[100] = "";
  char view[100] = "";
  long int view_id = -1;

  sscanf(argv, "%s %s %ld", input, view, &view_id);

  if (strcmp(view, "view") == 0) {
    if (view_id == -1) {
      printf("view id must be specified\n");
    }
  } else {
    printf("bad arguments syntax\n");
  }

  // check that view exists
  int view_exists = 0;
  if (a->nb_view == 0) {
    printf("no view in the aquarium\n");
  }

  for (int i = 0; i < a->nb_view; i++) {
    if (view_id == a->views[i]->id) {
      view_exists = 1;
      struct view *v = a->views[i];
      delete_view(a, v);
      printf("-> view %ld deleted\n", view_id);
    }
  }
  if (view_exists == 0) {
    printf("NOK : view doesn't exist in the aquarium\n");
  }
}