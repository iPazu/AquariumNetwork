#include "behavior.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

fish *classic_reproduction(fish *f1, fish *f2) {
    if (f1 == NULL || f2 == NULL)
        return NULL;

    if ((f1->species == f2->species) && (f1->gender == !(f2->gender))) {
        if (abs(f1->x - f2->x <= 1) && abs(f1->y - f2->y <= 1)) {
            fish *baby_fish =
                    init_fish("Baby", f1->x, f2->y, f1->speed, f1->strength, rand() % 2,
                              f1->species, f1->move, f1->reproduction, f1->hunting);
            printf("Reproduction de %s et %s\n", f1->name, f2->name);
            return baby_fish;
        }
    }

    return NULL;
}

fish *no_hunting(__attribute__((unused)) fish *f1, __attribute__((unused)) fish *f2) {
    return NULL;
}

fish *classic_hunting(fish *f1, fish *f2) {
    if (f1 == NULL || f2 == NULL)
        return NULL;

    if (f1->species != f2->species) {
        if (abs(f1->x - f2->x <= 1) && abs(f1->y - f2->y <= 1)) {
            if (f1->strength > f2->strength) {
                printf("%s a tué %s\n", f1->name, f2->name);
                return f2;
            } else {
                printf("%s a tué %s\n", f2->name, f1->name);
                return f1;
            }
        }
    }
    return NULL;
}

// Predators hunt their prey in a 15x15 square around them
fish *predator_hunting(fish *f1, fish *f2) {
    if (f1 == NULL || f2 == NULL)
        return NULL;

    if (f1->species != f2->species) {
        if (abs(f1->x - f2->x <= 15) && abs(f1->y - f2->y <= 15)) {
            if (f1->strength > f2->strength) {
                printf("%s a tué %s\n", f1->name, f2->name);
                return f2;
            } else {
                printf("%s a tué %s\n", f2->name, f1->name);
                return f1;
            }
        }
    }
    return NULL;
}