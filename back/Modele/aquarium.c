//
// Created by Axel PETIT on 12/04/2023.
//

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "aquarium.h"

aquarium *init_aquarium(int x_max, int y_max, int nb_fish, fish *fishes[MAX_FISH]) {
    aquarium *a = malloc(sizeof(aquarium));
    a->width = x_max;
    a->height = y_max;
    a->nb_fish = nb_fish;
    return a;
}

aquarium *init_aquarium_from_file(char *file_name) {
    aquarium *a = malloc(sizeof(aquarium));
    a->nb_fish = 0;
    a->nb_view = 0;

    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier text.txt\n");
    }

    char buffer[1024];
    // Read the first line for aquarium size
    fgets(buffer, sizeof(buffer), file);
    sscanf(buffer, "%dx%d", &a->width, &a->height);

    // Read the views
    while (fgets(buffer, sizeof(buffer), file)) {
        strtok(buffer, "\n\r");
        printf("Ligne lue : %s\n", buffer);
        view *view = create_view_from_string(buffer);
        add_view(a, view);
    }

    fclose(file);

    printf("Aquarium initialized from file %s\n", file_name);
    show_aquarium(a);

    return a;

}

void add_fish(aquarium *a, fish *f) {
    a->fishes[a->nb_fish] = f;
    a->nb_fish++;
    printf("Fish %s added, %d fish in the aquarium\n", f->name, a->nb_fish);
}

void move_fishes(aquarium *a) {
    for (int i = 0; i < a->nb_fish; i++) {
        a->fishes[i]->move(a->fishes[i], a->width, a->height);
        printf("Fish %s moved to %d, %d\n", a->fishes[i]->name, a->fishes[i]->x, a->fishes[i]->y);
    }
}

void delete_fish(aquarium *a, fish *f) {
    for (int i = 0; i < a->nb_fish; i++) {
        if (a->fishes[i] == f) {
            a->fishes[i] = a->fishes[a->nb_fish - 1];
            a->nb_fish--;
            break;
        }
    }
    printf("Fish %s deleted\n", f->name);
    free(f);
}

void show_aquarium(aquarium *a) {
    printf("Aquarium:\n\tWidth: %d\n\tHeight: %d\n\tNb fish: %d\n\tNb view: %d\n", a->width, a->height, a->nb_fish,
           a->nb_view);
}

void show_aquarium_views(aquarium *a) {
    printf("--------------\n");
    for (int i = 0; i < a->nb_view; i++) {
        show_view(a->views[i]);
    }
    printf("--------------\n");
}

void add_view(aquarium *a, view *v) {
    if (a->nb_view >= MAX_VIEW) {
        printf("Error: too many views in the aquarium");
        exit(1);
    }
    for (int i = 0; i < a->nb_view; i++) {
        if (a->views[i]->id == v->id) {
            printf("Error: view %d already exists in the aquarium", v->id);
            exit(1);
        }
    }
    a->views[a->nb_view] = v;
    a->nb_view++;
    show_aquarium_views(a);
    // printf("View %d added, %d views in the aquarium\n", v->id, a->nb_view);
}

void delete_view(aquarium *a, view *v) {
    for (int i = 0; i < a->nb_view; i++) {
        if (a->views[i] == v) {
            a->views[i] = a->views[a->nb_view - 1];
            a->nb_view--;
            break;
        }
    }
    printf("View %d deleted\n", v->id);
    free(v);
}

void save_aquarium(aquarium *a, char *file_name) {
    FILE *file = fopen(file_name, "w");
    if (file == NULL) {
        printf("Error while opening the file %s\n", file_name);
        exit(1);
    }
    fprintf(file, "%dx%d\n", a->width, a->height);
    for (int i = 0; i < a->nb_view; i++) {
        show_view(a->views[i]);
        fprintf(file, "N%d %dx%d+%d+%d\n", a->views[i]->id, a->views[i]->x,
                a->views[i]->y, a->views[i]->width, a->views[i]->height);
    }
    fclose(file);
    printf("Aquarium saved in %s\n", file_name);
}

int main() {
    srand(time(NULL));
    aquarium *a = init_aquarium_from_file("../loader.txt");

    save_aquarium(a, "../save.txt");


    free(a);
    return 0;
}
