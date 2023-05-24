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
#include "main.h"

pthread_t thread;
pthread_t thread2;

int running_status = 1;

void sigint_handler(int sig) {
    printf("\nReceived SIGINT signal! Cleaning up and terminating...\n");
    running_status = 0;
    pthread_cancel(thread);
    pthread_cancel(thread2);
    exit(0);
}

int main(int argc, char const *argv[]) {

    running_status = 1;
    aquarium *a = init_aquarium(5000, 4370, 0, 0);

    // create and add 2 views
    view *v1 = init_view(0, 0, 0, 500, 500);
    view *v2 = init_view(1, 500, 0, 500, 500);
    add_view(a, v1);
    add_view(a, v2);
    
    fish *f;
    f = init_basic_fish("A", 500, 250, 10, 5, "RandomWayPoint");
    f->is_started = 1;
    add_fish(a, f);
    f = init_basic_fish("B", 500, 250, 10, 5, "RandomWayPoint");
    f->is_started = 1;
    add_fish(a, f);
    f = init_basic_fish("C", 500, 250, 10, 5, "RandomWayPoint");
    f->is_started = 1;
    add_fish(a, f);

    fish *f1 = init_basic_fish("Norbert", 200, 400, 10, 5, "RandomWayPoint");
    fish *f2 = init_basic_fish("Robert",700, 700, 10, 5, "RandomWayPoint");
    f1->is_started = 1;
    f2->is_started = 1;
    add_fish(a, f1);
    add_fish(a, f2);

    pthread_create(&thread, NULL, (void *) start_server, a);
    pthread_create(&thread2, NULL, (void *) handle_aquarium, a);
    //handle_aquarium(a);
    while (running_status) {
       server_get_input(a);
    }
}
