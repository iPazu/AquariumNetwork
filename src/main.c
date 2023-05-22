#include "Controller/handler_server.h"
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
pthread_t thread2;

int main(int argc, char const *argv[]) {
    // gestion de la mémoire (en cas d'allocation dynamique)
    //    struct sigaction sa, old;
    //    sa.sa_handler = clean;
    //    sigset_t mask;
    //    sigemptyset(&sa.sa_mask);
    //    sa.sa_flags = 0;
    //    sigaction(SIGKILL, &sa, &old);

    aquarium *a = malloc(sizeof(aquarium));


    pthread_create(&thread, NULL, (void *) start_server, a);
    pthread_create(&thread2, NULL, (void *) handle_aquarium, a);

    while (1) {
       server_get_input(a);
    }
}
