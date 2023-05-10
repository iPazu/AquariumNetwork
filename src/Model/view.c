#include "view.h"
#include <stdio.h>
#include <stdlib.h>

view *init_view(int id, int x, int y, int width, int height) {
  if (width <= 0 || height <= 0) {
    printf("Error: width and height must be positive\n");
    return NULL;
  }
  if (x < 0 || y < 0) {
    printf("Error: x and y must be positive\n");
    return NULL;
  }
  view *v = malloc(sizeof(view));
  v->id = id;
  v->x = x;
  v->y = y;
  v->width = width;
  v->height = height;
  v->is_assigned = -1;
  return v;
}

void show_view(view *v) {
  printf("View %d:\n x: %d, y: %d, width: %d, height: %d, is_assigned: %d\n", v->id, v->x, v->y, v->width, v->height, v->is_assigned);
}

void attribute_view(view *v) {
  if (!v->is_assigned) {
    v->is_assigned = 1;
  }
}