#include "aquarium.h"
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

int nb_views = 4;
int nb_fishes = 10; // get it into struct aquarium

void clean() {} // to use in case of dynamic allocation

void get_option() {
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
               nb_fishes);
      }
      // addFish
      else if (strcmp(split, "addFish\n") == 0 && nb_tokens == 1) {
        printf("%s", fish_arg);

      } else if (strcmp(split, "addFish") == 0 && nb_tokens == 1) {
        printf("ajout d'un poisson\n");
        split = strtok(NULL, s);
        char *fish = split;
        printf("%s", fish);
        // if fish is in aquarium
        // aquarium_add_fish(fish); and fish_init call ?
      }

      // delFish
      else if (strcmp(split, "delFish\n") == 0 && nb_tokens == 1) {
        printf("%s", fish_arg);

      } else if (strcmp(split, "delFish") == 0 && nb_tokens == 1) {
        printf("supression d'un poisson\n");
        split = strtok(NULL, s);
        char *fish = split;
        printf("%s", fish);
        // if fish is in aquarium
        // aquarium_delete_fish();
        // else
        // printf("-> NOK : Poisson inexistant");

      }
      // getFishes
      else if (strcmp(split, "getFishes\n") == 0 && nb_tokens == 1) {
        printf("list\n"); // struct aquarium
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
        split = strtok(NULL, s);
        split = strtok(NULL, s);
        char *id = strtok(NULL, s);
        // if (id is a display view name)
        // printf("greeting %s\n", id);
        // else (invalid id)
        // printf("no greeting\n");
      }

      /*
        Programme contrôleur
      */

      // load
      else if (strcmp(split, "load\n") == 0 && nb_tokens == 1) {
        printf("%s", aq_arg);
      } else if (strcmp(split, "load") == 0 && nb_tokens == 1) {
        printf("aquarium\n");
        split = strtok(NULL, s);
        char *aquarium_id = split;
        printf("aquarium loaded (%d display view)\n", nb_views);
      }
      // show
      else if (strcmp(split, "show\n") == 0 && nb_tokens == 1) {
        printf("%s", aq_arg);

      } else if (strcmp(split, "show") == 0 && nb_tokens == 1) {
        split = strtok(NULL, s);
        if (strcmp(split, "aquarium") == 0)
          printf("display aquarium views and their dimension\n");
      }
      // save
      else if (strcmp(split, "save\n") == 0 && nb_tokens == 1) {
        printf("%s", aq_arg);

      } else if (strcmp(split, "save") == 0 && nb_tokens == 1) {
        printf("aquarium\n");
        split = strtok(NULL, s);
        printf("-> Aquarium saved ! (5 display view)\n"); // get real number of
                                                          // views
      }
      // del
      else if (strcmp(split, "del\n") == 0 && nb_tokens == 1) {
        printf("view and view number argument missing\n");

      } else if (strcmp(split, "del") == 0 && nb_tokens == 1) {
        // printf("aquarium\n");
        split = strtok(NULL, s);
        split = strtok(NULL, s);
        char *view = split;
        printf("-> view %s deleted\n", view);
      }
      // add
      else if (strcmp(split, "add") == 0 && nb_tokens == 1) {
        // printf("aquarium\n");
        split = strtok(NULL, s);
        split = strtok(NULL, s);
        // add view number to view file
        split = strtok(NULL, s);
        // add view dimensions to view file
        printf("-> view added\n");
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

  pthread_create(&thread, NULL, (void *)start_server, arg);
  while (1) {
    get_option();
  }
  return 0;
}
