#ifndef AQUARIUM_C
#define AQUARIUM_C

#define MAX_FISHES 100
#define AQUA_SIZE 100

#include <stdlib.h>
#include <unistd.h>

typedef struct fish fish;

struct fish
{
    int x;
    int y;
    void (*update)(fish *);
    int speed;
};

typedef struct aquarium
{
    int max_x;
    int max_y;
    fish *fishes[MAX_FISHES];
    int nb_fishes;
} aquarium;

#endif
