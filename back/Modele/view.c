//
// Created by Axel PETIT on 12/04/2023.
//

#include <stdlib.h>
#include <stdio.h>
#include "view.h"

view *create_view_from_file(FILE *file) {
    view *view = malloc(sizeof(view));
    fscanf(file, "N%d %dx%d+%d+%d", &view->id, &view->x, &view->y, &view->width, &view->height);
    return view;
}

view *create_view_from_string(char *string) {
    view *view = malloc(sizeof(view));
    sscanf(string, "N%d %dx%d+%d+%d", &view->id, &view->x, &view->y, &view->width, &view->height);
    return view;
}

view *create_view(int id, int x, int y, int width, int height) {
    view *view = malloc(sizeof(view));
    view->id = id;
    view->x = x;
    view->y = y;
    view->width = width;
    view->height = height;
    return view;
}

void show_view(view *v) {
    printf("View %d: %d, %d, %d, %d\n", v->id, v->x, v->y, v->width, v->height);
}