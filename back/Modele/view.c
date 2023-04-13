//
// Created by Axel PETIT on 12/04/2023.
//

#include <stdio.h>
#include "view.h"

void show_view(view *v) {
    printf("View %d: %d, %d, %d, %d\n", v->id, v->x, v->y, v->width, v->height);
}