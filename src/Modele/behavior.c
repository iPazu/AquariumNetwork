//
// Created by Axel PETIT on 18/04/2023.
//

#include <stdlib.h>
#include <printf.h>
#include "behavior.h"

fish *classic_reproduction(fish * f1, fish * f2) {
    if ( f1 == NULL || f2 == NULL) return NULL;

    if ( (f1->species == f2->species) && (f1->gender == !(f2->gender))) {
        if (abs(f1->x - f2->x <= 1) && abs(f1->y - f2->y <= 1)) {
            fish * baby_fish = init_fish("Baby", f1->x, f2 -> y, f1->speed, f1->strength, rand() % 2, f1->species, f1->move, f1->reproduction, f1->hunting);
            printf("Reproduction de %s et %s\n", f1->name, f2->name);
            return baby_fish;
        }
    }

    return NULL;
}

fish *classic_hunting(fish *f1, fish *f2) {
    if ( f1 == NULL || f2 == NULL) return NULL;

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