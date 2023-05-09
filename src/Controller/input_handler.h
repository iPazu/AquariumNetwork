//
// Created by Axel PETIT on 28/04/2023.
//

#ifndef AQUARIUM_NETWORK_INPUT_HANDLER_H
#define AQUARIUM_NETWORK_INPUT_HANDLER_H

#include "../Model/aquarium.h"
#include "../Model/view.h"
#include <arpa/inet.h>
#include <printf.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define MESSAGE_SIZE 4000

void get_option_server(aquarium *a);

void get_option_client(aquarium *a, int client_id, int *socket);

void get_status(aquarium *a, int client_id, int *socket);

int client_add_fish(aquarium *a, char argv[], __attribute__((unused)) int argc);

int client_del_fish(aquarium *a, char argv[], __attribute__((unused)) int argc);

void client_get_fishes(aquarium *a, __attribute__((unused)) char argv[],
                       __attribute__((unused)) int argc);

void client_get_fishes_continuously(aquarium *a, char argv[],
                                    __attribute__((unused)) int argc);

void client_start_fish(aquarium *a, char argv[],
                       __attribute__((unused)) int argc);

void client_ls(aquarium *a, char argv[], int argc);

void client_add_view(aquarium *a, char argv[], int argc);

void client_del_view(aquarium *a, char argv[], int argc);

void client_show_aquarium(aquarium *a, char argv[], int argc);

void client_save_aquarium(aquarium *a, char argv[], int argc);

void client_welcome(__attribute__((unused)) aquarium *a,
                    __attribute__((unused)) char argv[],
                    __attribute__((unused)) int argc);

int client_quit(__attribute__((unused)) aquarium *a, char argv[],
                __attribute__((unused)) int argc);

void client_ping(__attribute__((unused)) aquarium *a,
                 __attribute__((unused)) char argv[],
                 __attribute__((unused)) int argc);

void handler_load(aquarium *a, char argv[], __attribute__((unused)) int argc);

void handler_load_aquarium(aquarium *a, char argv[],
                           __attribute__((unused)) int argc);

void handler_show(aquarium *a, __attribute__((unused)) char argv[],
                  __attribute__((unused)) int argc);

void handler_show_aquarium(aquarium *a, __attribute__((unused)) char argv[],
                           __attribute__((unused)) int argc);

void views_interaction(aquarium *aqua, int *sock, int client_id,
                       char *client_message, int *view_id);

void handler_del_view(aquarium *a, char argv[], int argc);

void handler_add_view(aquarium *a, char argv[], int argc);

#endif // AQUARIUM_NETWORK_INPUT_HANDLER_H
