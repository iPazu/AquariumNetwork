#include "Controller/input_handler.h"
#include "Controller/tcp_server.h"
#include "Model/aquarium.h"
#include "Model/fish.h"
#include <assert.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

pthread_t thread;

int main(int argc, char const *argv[]) {
  // gestion de la mémoire (en cas d'allocation dynamique)
  //    struct sigaction sa, old;
  //    sa.sa_handler = clean;
  //    sigset_t mask;
  //    sigemptyset(&sa.sa_mask);
  //    sa.sa_flags = 0;
  //    sigaction(SIGKILL, &sa, &old);
  // aquarium *a = init_aquarium_from_file("../loader.txt");

  aquarium *a = init_aquarium(1000, 1000, 0, 0);

  // create and add 2 views
  view *v1 = init_view(0, 0, 0, 500, 500);
  view *v2 = init_view(1, 500, 500, 500, 500);
  add_view(a, v1);
  add_view(a, v2);

  pthread_create(&thread, NULL, (void *)start_server, a);

  while (1) {
    get_option_server(a);
  }
}
