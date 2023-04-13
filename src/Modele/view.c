//
// Created by Axel PETIT on 12/04/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include "view.h"

view *init_view(int id, int x, int y, int width, int height) {
    view *v = malloc(sizeof(view));
    v->id = id;
    v->x = x;
    v->y = y;
    v->width = width;
    v->height = height;
    return v;
}

void show_view(view *v) {
    printf("View %d: %d, %d, %d, %d\n", v->id, v->x, v->y, v->width, v->height);
}