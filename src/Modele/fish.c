//
// Created by Axel PETIT on 12/04/2023.
//

#include "fish.h"
#include "behavior.h"
#include "move.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void (*move_function(char *move_name))(fish *, int, int) {
    if (strcmp(move_name, "RandomPointWay") == 0) {
        return &RandomPointWay;
    }
    return &RandomPointWay;
}

fish *(*get_reproduction_function(char *behavior_name))(fish *, fish *) {
    if (strcmp(behavior_name, "Classic") == 0) {
        return &classic_reproduction;
    }
    return &classic_reproduction;
}

fish *(*get_hunting_function(char *behavior_name))(fish *, fish *) {
    if (strcmp(behavior_name, "Classic") == 0) {
        return &classic_hunting;
    }
    return &classic_hunting;
}

fish *init_fish(char *name, int x, int y, int speed, int strength, int gender,
                char *species, void (*move_function)(fish *, int, int),
                fish *(*reproduction_function)(fish *, fish *),
                fish *(*hunting_function)(fish *, fish *)) {
    fish *f = malloc(sizeof(fish));
    f->name = name;
    f->x = x;
    f->y = y;
    f->speed = speed;
    f->strength = strength;
    f->is_started = 0;
    f->gender = gender;
    f->species = species;
    f->move = move_function;
    f->reproduction = reproduction_function;
    f->hunting = hunting_function;

    return f;
}

fish *init_fish_from_client(char *name, int x, int y, int speed, int strength,
                            int gender, char *species, char *move_name,
                            char *reproduction_name, char *hunting_name) {
    fish *f = malloc(sizeof(fish));
    f->name = name;
    f->x = x;
    f->y = y;
    f->speed = speed;
    f->strength = strength;
    f->gender = gender;
    f->is_started = 0;
    f->species = species;
    f->move = move_function(move_name);
    f->reproduction = get_reproduction_function(reproduction_name);
    f->hunting = get_hunting_function(hunting_name);

    return f;
}

fish *init_basic_fish(char *name, int x, int y, char *move_name) {
    fish *f = malloc(sizeof(fish));
    f->name = name;
    f->x = x;
    f->y = y;
    f->speed = 1;
    f->strength = 1;
    f->gender = rand() % 2;
    f->is_started = 0;
    f->species = "Basic";
    f->move = move_function(move_name);
    f->reproduction = get_reproduction_function("Classic");
    f->hunting = get_hunting_function("Classic");
    return f;
}

void move_fish(fish *f, int x_max_aquarium, int y_max_aquarium) {
    f->move(f, x_max_aquarium, y_max_aquarium);
}

char *is_started(fish *f) {
    if (f->is_started) {
        return "started";
    } else {
        return "not started";
    }
}

void show_fish(fish *f) {
    printf("Fish %s is at (%d, %d) with speed %d, %s\n", f->name, f->x, f->y,
           f->speed, is_started(f));
}
