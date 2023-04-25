//
// Created by Axel PETIT on 18/04/2023.
//

#include "behavior.h"
#include <stdio.h>
#include <stdlib.h>

fish *classic_reproduction(fish *f1, fish *f2) {
  if (f1 == NULL || f2 == NULL)
    return NULL;
  if (f1->species == f2->species) {
    if (abs(f1->x - f2->x <= 1) && abs(f1->y - f2->y <= 1)) {
      fish *baby_fish = malloc(sizeof(fish));
      baby_fish->name = "Baby";
      baby_fish->x = f1->x;
      baby_fish->y = f2->y;
      baby_fish->speed = f1->speed;
      baby_fish->strength = f1->strength;
      baby_fish->species = f1->species;
      baby_fish->move = f1->move;
      baby_fish->reproduction = f1->reproduction;
      baby_fish->hunting = f1->hunting;
      printf("Reproduction de %s et %s\n", f1->name, f2->name);
      return baby_fish;
    }
  }
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