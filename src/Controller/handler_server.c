// File to handle arguments given by server

#include "../Model/aquarium.h"

char *notFound = "-> NOK : commande introuvable\n";
/**
 * @brief Load the aquarium
 *
 * @param a Aquarium to load
 * @param argv  Additional arguments
 */
void server_load_aquarium(aquarium *a, char argv[]) {

  char input[100] = "";
  char aquarium_file[20] = "";
  char extra_argument[100] = "";

  // Get the server arguments
  sscanf(argv, "%s %s %s", input, aquarium_file, extra_argument);

  // Bad syntax case
  if (strcmp(extra_argument, "") != 0) {
    printf("Error: too many arguments, the command should be : load "
           "[AQUARIUM_FILE]\n");
    return;
  }
  // Another bad syntax case
  if (strcmp(aquarium_file, "") == 0) {
    printf("Error: aquarium file must be specified such as : load "
           "[AQUARIUM_FILE]\n");
    return;
  }
  int res = init_aquarium_from_file(a, aquarium_file);
  // Check if the aquarium file exists
  if (res == 1) {
    printf("Error: aquarium file not found\n");
    return;
  }
  // Proper syntax was given, so load the aquarium
  else {
    printf("-> aquarium loaded (%d display view) !\n", a->nb_view);
    return;
  }
}

/**
 * @brief Show the aquarium
 *
 * @param a Aquarium to show
 * @param argv Additional arguments
 */
void server_show_aquarium(aquarium *a, char argv[]) {

  char input[100] = "";
  char aquarium[100] = "";

  // Get the server arguments
  sscanf(argv, "%s %s", input, aquarium);

  // Bad syntax case
  if (strcmp(aquarium, "") == 0) {
    printf("Error: no aquarium loaded. Aquarium argument must be specified "
           "such as : show aquarium\n");
    return;
  }
  // Another bad syntax case
  if (strcmp(aquarium, "aquarium\0") != 0) {
    printf("Error : aquarium argument must be specified such as : show "
           "aquarium\n");
    return;
  }
  // Proper syntax was given, so show the aquarium and its views
  else {
    show_aquarium(a);
    show_aquarium_views(a);
  }
}

/**
 * @brief Save the aquarium
 *
 * @param a  Aquarium to save
 * @param argv  Additional arguments
 */
void server_save_aquarium(aquarium *a, char argv[]) {

  char input[100] = "";
  char aquarium_file[100] = "";

  // Get the server arguments
  sscanf(argv, "%s %s", input, aquarium_file);
  // Bad syntax case
  if (strcmp(aquarium_file, "") == 0) {
    printf("Error: aquarium file must be specified such as : save "
           "[AQUARIUM_FILE]\n");
    return;
  }
  // Proper syntax was given, so save the aquarium
  save_aquarium(a, aquarium_file);
}

/**
 * @brief Add a view to the aquarium
 *
 * @param a Aquarium from which to add the view
 * @param argv Additional arguments
 */
void server_add_view(aquarium *a, char argv[]) {

  char input[100] = "";
  char view[100] = "";
  long int view_id = -1;
  long int long_vue_x = -1, long_vue_y = -1, long_width = -1, long_height = -1;
  // Get the server arguments
  sscanf(argv, "%s %s %ld %ldx%ld+%ld+%ld", input, view, &view_id, &long_vue_x,
         &long_vue_y, &long_width, &long_height);

  // Check the arguments
  printf("view : %s\n", view);
  printf("view_id : %ld\n", view_id);
  printf("long_vue_x : %ld\n", long_vue_x);
  printf("long_vue_y : %ld\n", long_vue_y);
  printf("long_width : %ld\n", long_width);
  printf("long_height : %ld\n", long_height);

  // Check that the view fits into the aquarium
  if (strcmp(view, "view") != 0) {
    printf("Error : view must be specified as second parameter, such as : add "
           "view "
           "[VIEW_ID]\n");
    return;
  }
  // Check if the view arguments are valid
  if (view_id == -1 || long_vue_x == -1 || long_vue_y == -1 ||
      long_width == -1 || long_height == -1) {
    // Give proper syntax for the add view instruction
    printf("Error : incorrect format, required format is : 'add view [VIEW_ID] "
           "[X]x[Y]+[WIDTH]+[HEIGHT]'\n");
    return;
  }

  // Convert long arguments into int
  int id = (int)view_id;
  int x = (int)long_vue_x;
  int y = (int)long_vue_y;
  int width = (int)long_width;
  int height = (int)long_height;

  // If conditions are fulfilled, create a view and add it to the aquarium
  struct view *v = init_view(id, x, y, width, height);
  add_view(a, v);
  printf("-> view added\n");
  return;
}
/**
 * @brief Delete a view
 *
 * @param a Aquarium from which to delete the view
 * @param argv Additional arguments
 */
void server_del_view(aquarium *a, char argv[]) {

  char input[100] = "";
  char view[100] = "";
  long int view_id = -1;
  // Get the server arguments
  sscanf(argv, "%s %s %ld", input, view, &view_id);

  // Analyze the arguments
  if (strcmp(view, "view") == 0) {
    if (view_id == -1) {
      printf("Error : view ID must be specified such as : delete view "
             "<VIEW_ID> \n");
      return;
    }
  } else {
    printf("Error : bad syntax. Syntax should be such as : delete view "
           "<VIEW_ID>\n");
    return;
  }

  // Check that the view exists
  int view_exists = 0;
  if (a->nb_view == 0) {
    printf("Error : there is no view in the aquarium\n");
    return;
  }
  // Browse the list of aquarium views to see if it exists
  for (int i = 0; i < a->nb_view; i++) {
    // Delete it if it exists
    if (view_id == a->views[i]->id) {
      view_exists = 1;
      struct view *v = a->views[i];
      delete_view(a, v);
      printf("-> view %ld deleted\n", view_id);
      return;
    }
  }
  // Case where the view doesn't exist
  if (view_exists == 0) {
    printf("NOK : view doesn't exist in the aquarium\n");
    return;
  }
}

/**
 * @brief Get and analyze server inputs
 *
 * @param a Aquarium from which the server processes orders
 */
void server_get_input(aquarium *a) {
  int size_arg = 100;
  char arg[size_arg];
  // Get the server inputs and avoid bugs by replacing '\n' with '\0'
  if (fgets(arg, size_arg, stdin) != NULL) {
    arg[strcspn(arg, "\n")] = '\0'; // replace '\n' with '\0'.
    char input[100] = "";
    char input2[100] = "";

    // Get the server arguments
    sscanf(arg, "%s", input);

    // Analyze the server arguments
    if (strcmp(input, "load") == 0) {
      server_load_aquarium(a, arg);
    } else if (strcmp(input, "show") == 0) {
      server_show_aquarium(a, arg);
    } else if (strcmp(input, "add") == 0) {
      server_add_view(a, arg);
    } else if (strcmp(input, "del") == 0) {
      server_del_view(a, arg);
    } else if (strcmp(input, "save") == 0) {
      server_save_aquarium(a, arg);
    }
    // Entered command was not found
    else {
      printf("%s", notFound);
    }
  }
}