#ifndef AQUARIUM_NETWORK_HANDLER_SERVER_H
#define AQUARIUM_NETWORK_HANDLER_SERVER_H

#include "../Model/aquarium.h"

void server_get_input(aquarium *a);

void server_load_aquarium(aquarium *a, char argv[]);

void server_show_aquarium(aquarium *a, char argv[]);

void server_add_view(aquarium *a, char argv[]);

void server_del_view(aquarium *a, char argv[]);

void server_save_aquarium(aquarium *a, char argv[]);


#endif  // AQUARIUM_NETWORK_HANDLER_SERVER_H