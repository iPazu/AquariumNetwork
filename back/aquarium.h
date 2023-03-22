#ifndef AQUARIUM_C
#define AQUARIUM_C

#define MAX_FISHES 100
#define AQUA_SIZE 100

typedef struct fish
{
    int x;
    int y;
    void (*update)(fish *);
    int speed;
} fish;

typedef struct aquarium
{
    int max_x;
    int max_y;
    fish *fishes[MAX_FISHES];
    int nb_fishes;
} aquarium;

#endif
