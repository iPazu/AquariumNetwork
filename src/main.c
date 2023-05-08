#include "Controler/input_handler.h"
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

void get_option(aquarium *a) {
  int size_arg = 100;
  char arg[size_arg];
  if (fgets(arg, size_arg, stdin) != NULL) {
    arg[strcspn(arg, "\n")] = '\0'; // remplace '\n' par '\0'
    char input[100] = "";
    char input2[100] = "";

    sscanf(arg, "%s", input);

    if (strcmp(input, "status") == 0) {
      get_status(a);
    } else if (strcmp(input, "addFish") == 0) {
      client_add_fish(a, arg, size_arg);
    } else if (strcmp(input, "delFish") == 0) {
      client_del_fish(a, arg, size_arg);
    } else if (strcmp(input, "getFishes") == 0) {
      client_get_fishes(a, arg, size_arg);
    } else if (strcmp(input, "startFish") == 0) {
      client_start_fish(a, arg, size_arg);
    } else if (strcmp(input, "getFishesContinuously") == 0) {
      client_get_fishes_continuously(a, arg, size_arg);
    } else if (strcmp(input, "ls") == 0) {
      client_ls(a, arg, size_arg);
    } else if (strcmp(input, "hello") == 0) {
      client_welcome(a, arg, size_arg);
    } else if (strcmp(input, "log") == 0) {
      client_quit(a, arg, size_arg);
    } else if (strcmp(input, "ping") == 0) {
      client_ping(a, arg, size_arg);
    } else if (strcmp(input, "load") == 0) {
      handler_load_aquarium(a, arg, size_arg);
    } else if (strcmp(input, "show") == 0) {
      handler_show_aquarium(a, arg, size_arg);
    } else if (strcmp(input, "add") == 0) {
      handler_add_view(a, arg, size_arg);
    } else if (strcmp(input, "del") == 0) {
      handler_del_view(a, arg, size_arg);
    } else {
      printf("%s", notFound);
    }
  }
}

int main(int argc, char const *argv[]) {
  // gestion de la mémoire (en cas d'allocation dynamique)
  //    struct sigaction sa, old;
  //    sa.sa_handler = clean;
  //    sigset_t mask;
  //    sigemptyset(&sa.sa_mask);
  //    sa.sa_flags = 0;
  //    sigaction(SIGKILL, &sa, &old);
  aquarium *a = malloc(sizeof(struct aquarium *));
  init_aquarium_from_file(a, "../loader.txt");
  // pthread_create(&thread, NULL, (void *) start_server, arg);

  // aquarium *a = init_aquarium(1000, 1000, 0, 0);
  while (1) {
    get_option(a);
  }
  free(a);
  printf("free");
  return 0;
}