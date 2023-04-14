#include "aquarium.h"
#include "display_aquarium.h"
#include "tcp_server.h"
#include <pthread.h>
#include <signal.h>
#include <stdio.h>

pthread_t thread;
void *arg;
char *notFound = "-> NOK : commande introuvable\n";
char *valid_command = "-> OK\n";
char *too_arg = "Too many arguments\n";
char *fish_arg = "Fish argument missing\n";
char *aq_arg = "aquarium argument missing\n";
char *view_arg = "view and view number arguments are missing\n";

void clean() {} // to use in case of dynamic allocation

// fonction de gestion des arguments de la ligne de commande
void get_option(struct aquarium *a, struct display_aquarium *d) {
  // gestion des arguments
  char arg[100];
  int size_arg = 100;
  int nb_tokens = 0;
  int total_tokens = 0;
  const char s[2] = " ";
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

      if (strcmp(split, "status\n") == 0 && nb_tokens == 1) {
        printf("-> OK : Connecté au contrôleur, %d  poisson(s) trouvé(s)\n",
               a->nb_fishes);
        // return list of fishes
        for (int i = 0; i < a->nb_fishes; i++) {
          print_fish(a->fishes[i]);
        }
      }
      // addFish
      else if (strcmp(split, "addFish\n") == 0 && nb_tokens == 1) {
        printf("%s", fish_arg);

      } else if (strcmp(split, "addFish") == 0 && nb_tokens == 1) {
        char *name = strtok(NULL, s);
        char *at = strtok(NULL, s);
        char *coord = strtok(NULL, s);
        char *display_size = strtok(NULL, s);
        char *mob = strtok(NULL, s);
        printf("name: %s at:%s coord:%s display_size:%s mob:%s\n", name, at,
               coord, display_size, mob);
        strtok(coord, "x");
        if (strcmp(mob, "RandomWayPoint\n") == 0) {
          //  if fish is in aquarium
          // printf("NOK\n");
          // else
          // struct fish * fish = *fish_init(name, x, y, x_dim, y_dim);
          //  aquarium_add_fish(a, fish);
          printf("->OK\n");

        } else {
          printf("-> NOK : mode de mobilité non supporté\n");
        }

      }

      // delFish
      else if (strcmp(split, "delFish\n") == 0 && nb_tokens == 1) {
        printf("%s", fish_arg);

      } else if (strcmp(split, "delFish") == 0 && nb_tokens == 1) {
        printf("supression d'un poisson\n");
        char *name = strtok(NULL, s);
        printf("%s", name);
        // if (strcmp(name, a->name_fishes[])){
        //  aquarium_delete_fish(a, a->fishes[]);
        //}
        //
        //  else
        //  printf("-> NOK : Poisson inexistant");

      }
      // getFishes
      else if (strcmp(split, "getFishes\n") == 0 && nb_tokens == 1) {
        printf("list\n");
        for (int i = 0; i < a->nb_fishes; i++) {
          print_fish(a->fishes[i]);
        }
      }
      // startFish
      else if (strcmp(split, "startFish\n") == 0 && nb_tokens == 1) {
        printf("%s", fish_arg);
      } else if (strcmp(split, "startFish") == 0 && nb_tokens == 1) {
        printf("fish started\n");
        split = strtok(NULL, s);
        char *fish = split;
        printf("%s", fish);
        printf("%s", valid_command);

      }
      // getFishesContinuously
      else if (strcmp(split, "getFishesContinuously") == 0 && nb_tokens == 1) {
        printf("%s", too_arg);

      } else if (strcmp(split, "getFishesContinuously\n") == 0 &&
                 nb_tokens == 1) {
        printf("list\n");
      }
      // ls
      else if (strcmp(split, "ls\n") == 0 && nb_tokens == 1) {
        printf("list\n");
      }
      // hello
      else if (strcmp(split, "hello\n") == 0 && nb_tokens == 1) {
        // attribution aléatoire si que hello
        printf("greeting random\n");
      } else if (strcmp(split, "hello") == 0 && nb_tokens == 1) {
        // attribution non aléatoire
        split = strtok(NULL, s); // check that split is as
        split = strtok(NULL, s); // chech that split is in
        char *id = strtok(NULL, s);
        // if (id is a display view name)
        // printf("greeting %s\n", id);
        // else (invalid id)
        // printf("no greeting\n");
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
        split = strtok(NULL, s);
        printf("pong %s\n", split);
      }

      /*
        Programme contrôleur
      */

      // load aquarium
      else if (strcmp(split, "load\n") == 0 && nb_tokens == 1) {
        printf("%s", aq_arg);
      } else if (strcmp(split, "load") == 0 && nb_tokens == 1) {
        char *file_name = strtok(NULL, s);
        load_aquarium(d, file_name);
        printf("aquarium loaded (%d display view)\n", d->nb_display);
      }
      // show aquarium
      else if (strcmp(split, "show\n") == 0 && nb_tokens == 1) {
        printf("%s", aq_arg);
      } else if (strcmp(split, "show") == 0 && nb_tokens == 1) {
        split = strtok(NULL, s); // strcmp split = aquarium

        if (strcmp(split, "aquarium\n") == 0 && nb_tokens == 1) {
          show_aquarium(d);
        }

      }
      // save aquarium
      else if (strcmp(split, "save\n") == 0 && nb_tokens == 1) {
        printf("%s", aq_arg);
      } else if (strcmp(split, "save") == 0 && nb_tokens == 1) {
        char *file_name = strtok(NULL, s); // check que le file existe
        save_aquarium(d, file_name);
        printf("-> Aquarium saved ! (%d display view)\n", d->nb_display);
      }
      // del view
      else if (strcmp(split, "del\n") == 0 && nb_tokens == 1) {
        printf("%s", view_arg);
      } else if (strcmp(split, "del") == 0 && nb_tokens == 1) {
        // printf("aquarium\n");
        split = strtok(NULL, s);
        if (strcmp(split, "view") == 0) {
          char *id_view = strtok(NULL, s);
          printf("id view is %s\n", id_view);
          int id = atoi(id_view + 1);
          printf("%d\n", id);
          // check that view id exists
          // delete_view(d, id);
          printf("-> view %d deleted\n", id);
        } else {
          printf("view argument missing\n");
        }
      }
      // add view
      else if (strcmp(split, "add\n") == 0 && nb_tokens == 1) {
        printf("arguments are missing\n");

      } else if (strcmp(split, "add") == 0 && nb_tokens == 1) {
        // printf("aquarium\n");
        split = strtok(NULL, s);
        if (strcmp(split, "view") == 0) {

          char *id = strtok(NULL, s);
          // should add view number to view file
          printf("id : %s\n", id);
          char *split = strtok(NULL, s);

          if (split == NULL) {
            printf("view dimensions are missing\n");
          }
          const char delim[3] = "x+";
          char *dimensions = strtok(split, s);
          printf("%s\n", dimensions);
          // décomposer la chaîne de caractères dim pour récupérer N{num_view}
          char *vue_x = strtok(dimensions, "x");
          printf("%s\n", vue_x);
          char *vue_y = strtok(dimensions, "+");
          printf("%s\n", vue_y);

          char *vue_width = strtok(dimensions, "+");
          printf("vue width %s\n", vue_width);

          // problème avec vue height
          char *vue_height = strtok(dimensions, s);
          printf("vue height%s\n", vue_height);

          // add view dimensions to view file
          add_view(d, id, vue_x, vue_y, vue_width, vue_height);
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
  printf("%d\n", nb_tokens);
  nb_tokens = 0;
}

int main(int argc, char const *argv[]) {
  // gestion de la mémoire (en cas d'allocation dynamique)
  struct sigaction sa, old;
  sa.sa_handler = clean;
  sigset_t mask;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = 0;
  sigaction(SIGKILL, &sa, &old);
  struct display_aquarium *d = malloc(sizeof(struct display_aquarium));
  struct aquarium *a = malloc(sizeof(struct aquarium));
  // initialisation de l'aquarium
  aquarium_init(a);
  // aquarium_fill(a, 10);

  pthread_create(&thread, NULL, (void *)start_server, arg);
  // gestion des arguments de la ligne de commande
  while (1) {
    get_option(a, d);
  }
  free(a);
  free(d);
  return 0;
}
