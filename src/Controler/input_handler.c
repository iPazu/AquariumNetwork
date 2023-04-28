//
// Created by Axel PETIT on 28/04/2023.
//

#include <printf.h>
#include <string.h>
#include <stdlib.h>
#include "input_handler.h"

void get_status(aquarium *a) {
    // Check if the connexion is valid
    printf("-> OK : Connecté au contrôleur, %d  poisson(s) trouvé(s)\n",
           a->nb_fish);
    // Return list of fishes
    for (int i = 0; i < a->nb_fish; i++) {
        show_fish(a->fishes[i]);
    }
}

int client_add_fish(aquarium *a, char argv[], int argc) {
    // get arguments
    char input[100] = "";
    char fish_name[20] = "";
    long int long_x = -1, long_y = -1, view_width = -1, view_height = -1;
    char mobility_name[20] = "";
    sscanf(argv, "%s %s at %ldx%ld %ldx%ld %s", input, fish_name, &long_x, &long_y, &view_width, &view_height,
           mobility_name);

    // Check if the fish is valid
    if ((strcmp(fish_name, "") == 0) || long_x == -1 || long_y == -1 || view_width == -1 || view_height == -1 ||
        (strcmp(mobility_name, "") == 0)) {
        printf("Error: fish parameters are not valid\n");
        return -1;
    }
    // Check if the mobility is valid
    if (strcmp(mobility_name, "") == 0) {
        printf("Error: Unknown mobility\n");
        return -1;
    }
    // Check if the fish is already in the aquarium
    for (int i = 0; i < a->nb_fish; i++) {
        printf("Nom du poisson dans la boucle : %s\n", a->fishes[i]->name);
        printf("Nom du poisson à ajouter : %s\n", fish_name);
        if (strcmp(a->fishes[i]->name, fish_name) == 0) {
            printf("Error: fish %s already in the aquarium\n", fish_name);
            return -1;
        }
    }

    int x = (int) long_x;
    int y = (int) long_y;
    fish *f = init_basic_fish(fish_name, x, y, mobility_name);
    show_fish(f);
    add_fish(a, f);

    printf("OK\n");
    printf("Nom du poisson dans la boucle : %s\n", a->fishes[0]->name);
    return 0;
}

int client_del_fish(aquarium *a, char argv[], int argc) {
    // get arguments
    char input[100] = "";
    char fish_name[20] = "";
    sscanf(argv, "%s %s", input, fish_name);
    printf("Nom du poisson : %s\n", fish_name);

    // Check if the fish is valid
    if (strcmp(fish_name, "") == 0) {
        printf("Error: fish name must be specified\n");
        return -1;
    }
    // Check if the fish is already in the aquarium and delete it.
    int fish_found = 0;
    printf("Nb fish : %d\n", a->nb_fish);
    for (int i = 0; i < a->nb_fish; i++) {
        printf("Dans la boucle, Nom du poisson : %s\n", a->fishes[i]->name);
        if (strcmp(a->fishes[i]->name, fish_name) == 0) {
            fish_found = 1;
            delete_fish(a, a->fishes[i]);
            printf("OK\n");
            printf("Fish %s deleted\n", fish_name);
        }
    }
    if (fish_found == 0) {
        printf("Error: fish %s not found\n", fish_name);
        return -1;
    }
    return 0;
}

void client_get_fishes(aquarium *a, char argv[], int argc) {

    printf("list\n");
    for (int i = 0; i < a->nb_fish; i++) {
        show_fish(a->fishes[i]);
    }
}

int client_quit(aquarium *a, char argv[], int argc) {
    printf("bye\n");
    exit(0);
}

void client_ping(aquarium *a, char argv[], int argc) {
    printf("pong\n");
}
