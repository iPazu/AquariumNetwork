#include "Controler/tcp_server.h"
#include "Modele/aquarium.h"
#include "Modele/fish.h"
#include <assert.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

pthread_t thread;
void *arg;
char *notFound = "-> NOK : commande introuvable\n";
char *valid_command = "-> OK\n";
char *too_arg = "Too many arguments\n";
char *fish_arg = "Fish argument missing\n";
char *aq_arg = "Aquarium argument missing\n";
char *pos_arg = "Position argument missing\n";
char *unexistant_fish = "-> NOK : Poisson inexistant dans l'aquarium\n";
char *view_arg = "View argument missing\n";

void clean() {} // to use in case of dynamic allocation

void get_option(struct aquarium *a) {
  // gestion des arguments
  char arg[100];
  int size_arg = 100;
  int nb_tokens = 0;
  int total_tokens = 0;
  const char s[3] = " ,";
  char *fishname;
  if (fgets(arg, size_arg, stdin) != NULL) {
    char *split = strtok(arg, s);
    // parcours de la liste des arguments
    while (split != NULL) {
      nb_tokens++;
      total_tokens++;

      /*
        Programme affichage
      */

      // Get status
      if (strcmp(split, "status\n") == 0 && nb_tokens == 1) {
        // s'assurer que la connexion est bien faite
        printf("-> OK : Connecté au contrôleur, %d  poisson(s) trouvé(s)\n",
               a->nb_fish);
        // return list of fishes
        for (int i = 0; i < a->nb_fish; i++) {
          show_fish(a->fishes[i]);
        }
      }
      // Add a fish
      else if (strcmp(split, "addFish\n") == 0 && nb_tokens == 1) {
        printf("%s", fish_arg);

      } else if (strcmp(split, "addFish") == 0 && nb_tokens == 1) {
        char *name = strtok(NULL, s);

        // error if name already exists in the aquarium
        char *at = strtok(NULL, s);
        assert(strcmp(at, "at") == 0);
        // special case if no position argument
        if (at == NULL) {
          printf("%s", pos_arg);
        }
        char *coord = strtok(NULL, s);
        char *display_size = strtok(NULL, s);
        char *mob = strtok(NULL, s);
        printf("name: %s at:%s coord:%s display_size:%s mob:%s", name, at,
               coord, display_size, mob); // test

        // définir les différents modes de mobilité
        if (strcmp(mob, "RandomWayPoint\n") == 0) {

          //  if fish is in aquarium
          int is_fish_in = 0;
          for (int i = 0; i < a->nb_fish; i++) {
            if (a->fishes[i]->name == name) {
              is_fish_in = 1;
              printf("NOK, a fish with the same name already exists\n");
              return;
            }
          }
          //  if fish isn't in the aquarium
          if (is_fish_in == 0) {
            struct fish *fish =
                init_basic_fish(name, coord[0], coord[1], "RandomPointWay");
            add_fish(a, fish);
            printf("OK\n");
          }

        } else {
          printf("-> NOK : mode de mobilité non supporté\n");
        }

      }

      // Delete a fish
      else if (strcmp(split, "delFish\n") == 0 && nb_tokens == 1) {
        printf("%s", fish_arg);

      } else if (strcmp(split, "delFish") == 0 && nb_tokens == 1) {
        char *name = strtok(NULL, s);
        printf("%s", name);
        // check if fish exists
        int fish_exists = 0;
        for (int i = 0; i < a->nb_fish; i++) {
          if (strcmp(
                  name,
                  a->fishes[i]->name)) { // creation of a table of fish names ?
            fish_exists = 1;
            delete_fish(a, a->fishes[i]);
          }
        }
        printf("OK\n");
        if (fish_exists == 0)
          printf("%s", unexistant_fish);
      }
      // Get fishes list
      else if (strcmp(split, "getFishes\n") == 0 && nb_tokens == 1) {
        printf("list\n");
        for (int i = 0; i < a->nb_fish; i++) {
          show_fish(a->fishes[i]);
        }
      }
      // start a fish
      else if (strcmp(split, "startFish\n") == 0 && nb_tokens == 1) {
        printf("%s", fish_arg);
      } else if (strcmp(split, "startFish") == 0 && nb_tokens == 1) {
        split = strtok(NULL, s);

        // check if fish exists in the fishes list
        int fish_exists = 0;
        for (int i = 0; i < a->nb_fish; i++) {
          if (strcmp(split, a->fishes[i]->name)) {
            fish_exists = 1;
            // start fish
            move_fish(a->fishes[i], a->width, a->height);
            a->fishes[i]->is_started = 1;
            printf("%s", valid_command);
            printf("fish started\n");
          }
        }
        if (fish_exists == 0) {
          printf("%s", unexistant_fish);
          printf("%s\n", "NOK\n");
        }
      }
      // getFishesContinuously
      else if (strcmp(split, "getFishesContinuously") == 0 && nb_tokens == 1) {
        printf("%s", too_arg);
      } else if (strcmp(split, "getFishesContinuously\n") == 0 &&
                 nb_tokens == 1) {
        printf("list ");
        // gérer avec la connexion tcp, définir la fréquence d'affichage de la
        // liste
        for (int i = 0; i < a->nb_fish; i++) {
          show_fish(a->fishes[i]);
        }
      }
      // ls
      else if (strcmp(split, "ls\n") == 0 && nb_tokens == 1) {
        if (a->nb_fish == 0)
          printf("no fish in the aquarium\n");
        for (int i = 0; i < a->nb_fish; i++) {
          printf("list\n");
          show_fish(a->fishes[i]);
        }
      }
      // hello
      else if (strcmp(split, "hello\n") == 0 && nb_tokens == 1) {
        // attribution aléatoire si que hello (parcourir la liste des vues
        // dispo)
        printf("greeting random\n");
        char *random_id = "N1";
        for (int i = 0; i < a->nb_view; i++) {
        }
      } else if (strcmp(split, "hello") == 0 && nb_tokens == 1) {
        // attribution non aléatoire
        split = strtok(NULL, s);
        // check that split is "in"
        assert(strcmp(split, "in") == 0);

        split = strtok(NULL, s);
        // check that split is "as"
        assert(strcmp(split, "as") == 0);

        char *id = strtok(NULL, s);
        // check that ID exists in the aquarium
        int id_exists = 0;
        for (int i = 0; i < a->nb_view; i++) {
          char buf_num_view[32];
          sprintf(buf_num_view, "N%d", a->views[i]->id);
          if (strcmp(split, buf_num_view)) {
            id_exists = 1;
            printf("greeting %s\n", id);

            printf("%s", valid_command);
          }
        }
        if (id_exists == 0) {
          printf("no greeting\n");
        }
      }
      // log out
      else if (strcmp(split, "log") == 0 && nb_tokens == 1) {
        split = strtok(NULL, s);
        if (strcmp(split, "out\n") == 0) {
          printf("bye\n");
        }
      }
      // ping
      else if (strcmp(split, "ping") == 0 && nb_tokens == 1) {
        // define a time to delete a display program if it is not pinged
        // check that connection is still done
        split = strtok(NULL, s);
        printf("pong %s\n", split);
      }

      /*
        Programme contrôleur
      */

      // load an aquarium
      else if (strcmp(split, "load\n") == 0 && nb_tokens == 1) {
        printf("%s", aq_arg);
      } else if (strcmp(split, "load") == 0 && nb_tokens == 1) {
        char *file_name = strtok(NULL, s);
        // check that file exists
        if (access(file_name, F_OK) == 0) {
          a = init_aquarium_from_file(file_name);
          printf("aquarium loaded (%d display view) !\n", a->nb_view);
        } else {
          printf("Error : file not found\n");
        }
      }
      // show an aquarium
      else if (strcmp(split, "show\n") == 0 && nb_tokens == 1) {
        printf("%s", aq_arg);
      } else if (strcmp(split, "show") == 0 && nb_tokens == 1) {
        split = strtok(NULL, s);

        if (strcmp(split, "aquarium\n") == 0 && nb_tokens == 1) {
          show_aquarium(a);
          show_aquarium_views(a);
        }
      }
      // save an aquarium in a file
      else if (strcmp(split, "save\n") == 0 && nb_tokens == 1) {
        printf("%s", aq_arg);
      } else if (strcmp(split, "save") == 0 && nb_tokens == 1) {
        char *file_name = strtok(NULL, s);

        // check that file exists
        if (access(file_name, F_OK) == 0) {
          a = init_aquarium_from_file(file_name);
          printf("Aquarium saved ! (%d display view)\n", a->nb_view);
        } else {
          printf("Error : file not found\n");
        }
      }
      // delete a view
      else if (strcmp(split, "del\n") == 0 && nb_tokens == 1) {
        printf("view and view number arguments missing\n");
      } else if (strcmp(split, "del") == 0 && nb_tokens == 1) {
        // printf("aquarium\n");
        split = strtok(NULL, s);
        if (strcmp(split, "view") == 0) {
          char *num_view = strtok(NULL, s);

          // check if view exists in the aquarium
          int view_exists = 0;
          for (int i = 0; i < a->nb_view; i++) {
            int n_view = a->views[i]->id;
            printf("%d\n", n_view);
            // char buf_num_view[32];
            // sprintf(buf_num_view, "N%d", n_view);
            if (atoi(num_view) == n_view) {
              view_exists = 1;
              view *view_to_delete = a->views[n_view];
              delete_view(a, view_to_delete);
              printf("-> view %d deleted\n", n_view);
              return;
            }
          }
          if (view_exists == 0) {
            printf("can't delete the view, it doesn't exist\n");

          } else {
            printf("%s", view_arg);
          }
        }
      }
      // add a view
      else if (strcmp(split, "add") == 0 && nb_tokens == 1) {
        // printf("aquarium\n");
        split = strtok(NULL, s);

        if (strcmp(split, "view") == 0) {
          // check if the view number exists (to fix)
          char *num_view = strtok(NULL, s);
          // add view number to view file
          // char *id = strtok(NULL, s);
          // décomposer la chaîne de caractères dim pour récupérer
          // N{num_view}
          printf("analyzing new view arguments\n");

          char *vue_x = strtok(NULL, s);
          char *vue_y = strtok(NULL, "x");
          char *vue_width = strtok(NULL, "+");
          char *vue_height = strtok(NULL, "+");
          printf("analyzing new view arguments\n");

          int num_id = sscanf(vue_x, "%d", &num_id);
          int x = sscanf(vue_x, "%d", &x);
          int y = sscanf(vue_y, "%d", &y);
          int width = sscanf(vue_width, "%d", &width);
          int height = sscanf(vue_height, "%d", &height);
          printf("-> view analyzed\n");

          //  add view dimensions to view file
          view *v = init_view(num_id, x, y, width, height);
          add_view(a, v);
          printf("-> view added\n");
        } else {
          printf("view argument missing\n");
        }
      }
      // invalid command
      else if (nb_tokens == 1) {
        printf("%s", notFound);
      }
      split = strtok(NULL, s);
    }

    split = strtok(NULL, s);
  }
  // printf("%d\n", nb_tokens);
  // nb_tokens = 0;
}

int main(int argc, char const *argv[]) {
  // gestion de la mémoire (en cas d'allocation dynamique)
  struct sigaction sa, old;
  sa.sa_handler = clean;
  sigset_t mask;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = 0;
  sigaction(SIGKILL, &sa, &old);
  struct aquarium *a = malloc(sizeof(struct aquarium));
  a = init_aquarium_from_file("../loader.txt");
  // init_aquarium(a->width, a->height, a->nb_fish,a->nb_view); //
  // init_aquarium(); should initialize an empty struct
  pthread_create(&thread, NULL, (void *)start_server, arg);
  while (1) {
    get_option(a);
  }
  free(a);
  printf("free");
  return 0;
}
