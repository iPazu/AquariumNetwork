#include "handler_client.h"

char *notFoundClient = "-> NOK : commande introuvable\n";

// Get status
void client_status(aquarium *a, int client_id, int *socket, int *view_id) {
  char *buf = malloc(sizeof(char) * MESSAGE_SIZE);
  // Send info to proper client
  sprintf(buf, "-> OK : Connecté au contrôleur, %d  poisson(s) trouvé(s)\n",
          a->nb_fish);
  printf("SEND TO CLIENT %d: %s", client_id, buf);
  write(*socket, buf, strlen(buf));
  memset(buf, 0, MESSAGE_SIZE);

  // Initialize client view
  view *client_view = a->views[*view_id];

  // Return list of fishes
  for (int i = 0; i < a->nb_fish; i++) {
    // show_fish(a->fishes[i], buf);
    fish *f = a->fishes[i];
    // Translating coordinates in display size percentage
    int relative_x = f->x - client_view->x;
    int relative_y = f->y - client_view->y;
    int percentage_x = (relative_x * 100) / client_view->width;
    int percentage_y = (relative_y * 100) / client_view->height;
    // Send info to proper client
    sprintf(buf, "Fish %s at %dx%d, %dx%d, %s\n", f->name, percentage_x,
            percentage_y, f->width, f->height,
            (f->is_started) ? "started" : "stopped");
    printf("SEND TO CLIENT %d: %s", client_id, buf);
    write(*socket, buf, strlen(buf));
    memset(buf, 0, MESSAGE_SIZE);
  }
  free(buf);
}

// Add a fish
int client_add_fish(aquarium *a, char argv[], int client_id, int *socket,
                    int *view_id) {

  char input[100] = "";
  char *fish_name = malloc(sizeof(char) * 20);
  long int long_x = -1, long_y = -1, long_width = -1, long_height = -1;
  char mobility_name[20] = "";
  char *buf = malloc(sizeof(char) * MESSAGE_SIZE);

  // Get the client arguments
  sscanf(argv, "%s %s at %ldx%ld, %ldx%ld, %s", input, fish_name, &long_x,
         &long_y, &long_width, &long_height, mobility_name);

  // Check if the fish is valid
  if ((strcmp(fish_name, "") == 0) || long_x == -1 || long_y == -1 ||
      long_width == -1 || long_height == -1 ||
      (strcmp(mobility_name, "") == 0)) {
    // Send error to proper client
    sprintf(buf,
            "Error : incorrect format ! Required format is : 'addFish "
            "[FISH_NAME] at [FINAL_X]x[FINAL_Y], [FISH_WIDTH]x[FISH_HEIGHT], "
            "[MOBILITY]'\n");
    printf("SEND TO CLIENT %d: %s", client_id, buf);
    write(*socket, buf, strlen(buf));
    free(buf);
    return -1;
  }
  // Check if the mobility is valid
  if (strcmp(mobility_name, "") == 0) {
    sprintf(buf, "Error: Unknown mobility\n");
    printf("SEND TO CLIENT %d: %s", client_id, buf);
    write(*socket, buf, strlen(buf));
    free(buf);
    return -1;
  }
  // Check if the fish is already in the aquarium
  for (int i = 0; i < a->nb_fish; i++) {
    if (strcmp(a->fishes[i]->name, fish_name) == 0) {
      sprintf(buf, "Error: fish %s already in the aquarium\n", fish_name);
      printf("SEND TO CLIENT %d: %s", client_id, buf);
      write(*socket, buf, strlen(buf));
      free(buf);
      return -1;
    }
  }
  // Translating coordinates into display size percent
  view *client_view = a->views[*view_id];
  int percentage_x = (int)long_x;
  int percentage_y = (int)long_y;
  int width = (int)long_width;
  int height = (int)long_height;

  int relative_x = (percentage_x * client_view->width) / 100;
  int relative_y = (percentage_y * client_view->height) / 100;

  int absolute_x = relative_x + client_view->x;
  int absolute_y = relative_y + client_view->y;

  // Initialize fish with given data
  fish *f = init_basic_fish(fish_name, absolute_x, absolute_y, width, height,
                            mobility_name);
  // Add the fish to the aquarium
  add_fish(a, f);

  // Send info to proper client
  sprintf(buf, "OK\n");
  printf("SEND TO CLIENT %d: %s", client_id, buf);
  write(*socket, buf, strlen(buf));
  free(buf);
  return 0;
}

// Delete a fish
int client_del_fish(aquarium *a, char argv[], int client_id, int *socket) {

  char input[100] = "";
  char fish_name[20] = "";
  char *buf = malloc(sizeof(char) * MESSAGE_SIZE);

  // Get the client arguments
  sscanf(argv, "%s %s", input, fish_name);

  // Check if the fish is valid
  if (strcmp(fish_name, "") == 0) {
    sprintf(buf, "Error: fish name to delete must be specified as follows : "
                 "delFish [FISHNAME]\n");
    printf("SEND TO CLIENT %d: %s", client_id, buf);
    write(*socket, buf, strlen(buf));
    free(buf);
    return -1;
  }
  // Check if the fish is already in the aquarium and delete it if it's the
  // case.
  int fish_found = 0;
  // Browse the fish in the list of fishes in the aquarium
  for (int i = 0; i < a->nb_fish; i++) {
    // Delete the fish if it was found in the list
    if (strcmp(a->fishes[i]->name, fish_name) == 0) {
      fish_found = 1;
      delete_fish(a, a->fishes[i]);
      // Send the info to the proper client
      sprintf(buf, "OK\n");
      printf("SEND TO CLIENT %d: %s", client_id, buf);
      write(*socket, buf, strlen(buf));
      free(buf);
    }
  }
  // Case where the fish wasn't found in the aquarium
  if (fish_found == 0) {
    sprintf(buf, "NOK : %s inexistant\n", fish_name);
    printf("SEND TO CLIENT %d: %s", client_id, buf);
    write(*socket, buf, strlen(buf));
    free(buf);
    return -1;
  }
  return 0;
}

// Start a fish
void client_start_fish(aquarium *a, char argv[], int client_id, int *socket) {
  char input[100] = "";
  char fish_name[20] = "";
  char *buf = malloc(sizeof(char) * MESSAGE_SIZE);

  // Get the client arguments
  sscanf(argv, "%s %s", input, fish_name);

  // Check that the fish is valid
  if (strcmp(fish_name, "") == 0) {
    sprintf(buf, "Error: fish name must be specified\n");
    printf("SEND TO CLIENT %d: %s", client_id, buf);
    write(*socket, buf, strlen(buf));
    free(buf);
    return;
  }
  // Check if the fish is already in the aquarium and start it.
  int fish_found = 0;
  for (int i = 0; i < a->nb_fish; i++) {
    if (strcmp(a->fishes[i]->name, fish_name) == 0) {
      fish_found = 1;
      if (a->fishes[i]->is_started == 1) {
        sprintf(buf, "Error: fish %s already started\n", fish_name);
        printf("SEND TO CLIENT %d: %s", client_id, buf);
        write(*socket, buf, strlen(buf));
        free(buf);
        return;
      }
      a->fishes[i]->is_started = 1;
      sprintf(buf, "OK\n");
      printf("SEND TO CLIENT %d: %s", client_id, buf);
      write(*socket, buf, strlen(buf));
      free(buf);
      return;
    }
  }
  // Case where the fish wasn't found
  if (fish_found == 0) {
    printf("Error: fish %s not found\n", fish_name);
    sprintf(buf, "Error: fish %s not found\n", fish_name);
    printf("SEND TO CLIENT %d: %s", client_id, buf);
    write(*socket, buf, strlen(buf));
    free(buf);
    return;
  }
}

// Quit
int client_quit(char argv[], int client_id, int *socket) {

  char *buf = malloc(sizeof(char) * MESSAGE_SIZE);
  char input[100] = "";
  char option[20] = "";
  char extra_argument[100] = "";

  // Get the client arguments
  sscanf(argv, "%s %s %s", input, option, extra_argument);
  // Too many arguments in the client input
  if (strcmp(extra_argument, "") != 0) {
    sprintf(buf, "Error: too many arguments\n");
    printf("SEND TO CLIENT %d: %s", client_id, buf);
    write(*socket, buf, strlen(buf));
    free(buf);
    return -1;
  }
  // Proper input
  if (strcmp(option, "out") == 0) {
    sprintf(buf, "bye\n");
    printf("SEND TO CLIENT %d: %s", client_id, buf);
    write(*socket, buf, strlen(buf));
    free(buf);
    exit(0);
  }
  // Case of wrong client input
  sprintf(buf, "Invalid option, quit command is : log out\n");
  printf("SEND TO CLIENT %d: %s", client_id, buf);
  write(*socket, buf, strlen(buf));
  free(buf);
  return -1;
}

// Welcome
void client_welcome(aquarium *a, char argv[], int client_id, int *socket,
                    int *view_id) {

  char *buf = malloc(sizeof(char) * MESSAGE_SIZE);
  char input[100] = "";
  char as[20] = "";
  char in[100] = "";
  char id[100] = "";

  // Get client arguments
  sscanf(argv, "%s %s %s %s", input, in, as, id);
  // Check the arguments
  if (strlen(in) == 0 && strlen(as) == 0 && strlen(id) == 0) {
    int available_views[MAX_VIEW];
    int nb_available_views = 0;
    // Check if some views are available
    for (int i = 0; i < a->nb_view; i++) {
      if (a->views[i]->is_assigned == -1) {
        available_views[nb_available_views] = i;
        nb_available_views++;
      }
    }
    // Choose a random view if several views are available
    if (nb_available_views > 0) {
      // If no view ID in argument, attribute random available view
      *view_id = available_views[rand() % nb_available_views];
      a->views[*view_id]->is_assigned = client_id;
      // Send the info to proper client
      printf("VIEW ID: %d\n", *view_id);
      sprintf(buf, "greeting %d\n", *view_id);
      printf("SEND TO CLIENT %d: %s", client_id, buf);
      write(*socket, buf, strlen(buf));
      free(buf);
      return;
    }

    // Attribute available view given in parameter
  } else if (strcmp(in, "in") == 0 && strcmp(as, "as") == 0 &&
             strlen(id) != 0) {
    int view_exists = 0;
    // Check if the view exists
    for (int i = 0; i < a->nb_view; i++) {
      if (atoi(id) == a->views[i]->id) {
        view_exists = 1;
      }
    }
    // Case where the view doesn't exist
    if (view_exists == 0) {
      sprintf(buf, "Error: view %d doesn't exist\n", atoi(id));
      printf("SEND TO CLIENT %d: %s", client_id, buf);
      write(*socket, buf, strlen(buf));
      free(buf);
      return;
    }
    // Check if the view is available
    if (a->views[atoi(id)]->is_assigned == -1) {
      a->views[atoi(id)]->is_assigned = client_id;
      *view_id = atoi(id);
      sprintf(buf, "greeting %d\n", atoi(id));
      printf("SEND TO CLIENT %d: %s", client_id, buf);
      write(*socket, buf, strlen(buf));
      free(buf);
      return;
    }
    // Case where the view is unavailable
    else {
      sprintf(buf, "Error: view %d is unavailable\n", atoi(id));
      printf("SEND TO CLIENT %d: %s", client_id, buf);
      write(*socket, buf, strlen(buf));
      free(buf);
    }
  }
  // Case of bad syntax of client input
  else if (strcmp(in, "in") != 0 || strcmp(as, "as") == 0) {
    sprintf(
        buf,
        "Bad syntax, try again. Proper syntax is : hello in as <VIEW_ID>\n");
    printf("SEND TO CLIENT %d: %s", client_id, buf);
    write(*socket, buf, strlen(buf));
    free(buf);
  }
  // Another case of bad syntax of client input
  else {
    sprintf(
        buf,
        "Bad syntax, try again. Proper syntax is : hello in as <VIEW_ID>\n");
    printf("SEND TO CLIENT %d: %s", client_id, buf);
    write(*socket, buf, strlen(buf));
    free(buf);
  }
}

// Get fishes
void client_get_fishes(aquarium *a, int client_id, int *socket) {

  char *buf = malloc(sizeof(char) * MESSAGE_SIZE);

  // Case where there is no fish are in the aquarium
  if (a->nb_fish == 0) {
    sprintf(buf, "No fish in the aquarium\n");
    printf("SEND TO CLIENT %d: %s", client_id, buf);
    write(*socket, buf, strlen(buf));
    free(buf);
    return;
  }

  sprintf(buf, "list\n");

  // Loop on all fishes of the aquarium
  for (int i = 0; i < a->nb_fish; i++) {
    show_fish(a->fishes[i], buf);
  }
  // Send info to proper client
  printf("SEND TO CLIENT %d: %s", client_id, buf);
  write(*socket, buf, strlen(buf));
  free(buf);
}

// ls
void client_ls(aquarium *a, int client_id, int *socket) {

  char *buf = malloc(sizeof(char) * MESSAGE_SIZE);
  // Case where there is no fish in the aquarium
  if (a->nb_fish == 0) {
    sprintf(buf, "No fish in the aquarium\n");
    printf("SEND TO CLIENT %d: %s", client_id, buf);
    write(*socket, buf, strlen(buf));
    free(buf);
    return;
  }
  // Send the fishes list to proper client
  sprintf(buf, "list ");
  printf("SEND TO CLIENT %d: %s", client_id, buf);
  write(*socket, buf, strlen(buf));
  memset(buf, 0, MESSAGE_SIZE);

  char *fishes = malloc(sizeof(char) * 1000);

  for (int i = 0; i < a->nb_fish; i++) {
    show_fish_ls(a->fishes[i], buf);
    char *tmp = malloc(sizeof(char) * 10);
    sprintf(tmp, "%d", i);
    strcat(fishes, tmp);
    strcat(fishes, " ");
    free(tmp);
  }
  free(buf);
}

void client_get_fishes_continuously(aquarium *a, int client_id, int *socket) {

  char *buf = malloc(sizeof(char) * MESSAGE_SIZE);
  // Case where there is no fish in the aquarium
  if (a->nb_fish == 0) {
    sprintf(buf, "No fish in the aquarium\n");
    printf("SEND TO CLIENT %d: %s", client_id, buf);
    write(*socket, buf, strlen(buf));
    free(buf);
    return;
  }
  // Send the fishes list to proper client
  sprintf(buf, "list ");
  printf("SEND TO CLIENT %d: %s", client_id, buf);
  write(*socket, buf, strlen(buf));
  memset(buf, 0, MESSAGE_SIZE);

  char *fishes = malloc(sizeof(char) * 1000);
  for (int i = 0; i < a->nb_fish; i++) {
    show_fish_ls(a->fishes[i], buf);
    char *tmp = malloc(sizeof(char) * 10);
    sprintf(tmp, "%d", i);
    strcat(fishes, tmp);
    strcat(fishes, " ");
    free(tmp);
  }
  free(buf);
}

// ping
void client_ping(char argv[], int client_id, int *socket) {

  char input[100] = "";
  int option = -1;
  char *buf = malloc(sizeof(char) * MESSAGE_SIZE);

  // Get the client arguments
  sscanf(argv, "%s %d", input, &option);

  if (option == -1) {
    // No more argument
    sprintf(buf, "pong\n");
    printf("SEND TO CLIENT %d: %s", client_id, buf);
    write(*socket, buf, strlen(buf));
    free(buf);
  } else {
    // Additional argument
    sprintf(buf, "pong %d\n", option);
    printf("SEND TO CLIENT %d: %s", client_id, buf);
    write(*socket, buf, strlen(buf));
    free(buf);
  }
}

void views_interaction(aquarium *aqua, int *sock, int client_id,
                       char *client_message) {
  int read_size;
  // Create a str with all available views ID
  char *views = malloc(sizeof(char) * 1000);

  for (int i = 0; i < aqua->nb_view; i++) {
    if (aqua->views[i]->is_assigned == -1) {
      show_view(aqua->views[i]);
      char *tmp = malloc(sizeof(char) * 10);
      sprintf(tmp, "%d", i);
      strcat(views, tmp);
      strcat(views, " ");
      free(tmp);
    }
  }

  write(*sock, views, strlen(views));
  printf("SEND TO CLIENT %d: %s\n", client_id, views);
  free(views);
}
/**
 * @brief function to get the client inputs
 *
 * @param a aquarium
 * @param client_id client id
 * @param socket socket number
 * @param client_message
 * @param view_id
 */
void client_get_input(aquarium *a, int client_id, int *socket,
                      char *client_message, int *view_id) {

  char *arg = client_message;
  char input[100] = "";

  // Get the client input
  sscanf(arg, "%s", input);

  if (strcmp(input, "status") == 0) {
    client_status(a, client_id, socket, view_id);
  } else if (strcmp(input, "addFish") == 0) {
    client_add_fish(a, arg, client_id, socket, view_id);
  } else if (strcmp(input, "delFish") == 0) {
    client_del_fish(a, arg, client_id, socket);
  } else if (strcmp(input, "getFishes") == 0) {
    client_get_fishes(a, client_id, socket);
  } else if (strcmp(input, "startFish") == 0) {
    client_start_fish(a, arg, client_id, socket);
  } else if (strcmp(input, "getFishesContinuously") == 0) {
    client_get_fishes_continuously(a, client_id, socket);
  } else if (strcmp(input, "ls") == 0) {
    client_ls(a, client_id, socket);
  } else if (strcmp(input, "hello") == 0) {
    client_welcome(a, arg, client_id, socket, view_id);
  } else if (strcmp(input, "log") == 0) {
    client_quit(arg, client_id, socket);
  } else if (strcmp(input, "ping") == 0) {
    client_ping(arg, client_id, socket);
  } else {
    char *buf = malloc(sizeof(char) * MESSAGE_SIZE);

    sprintf(buf, "%s", notFoundClient);
    printf("SEND TO CLIENT %d: %s", client_id, buf);
    write(*socket, buf, strlen(buf));
    free(buf);
  }
}