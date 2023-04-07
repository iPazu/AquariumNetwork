#include "display_aquarium.h"
#include <stdio.h>
#include <stdlib.h>

void load_aquarium(display_aquarium *d, char *file_name) {
  printf("to be done\n");
}
void save_aquarium(display_aquarium *d, char *file_name) {
  printf("to be done\n");
}
void show_aquarium(display_aquarium *d) {
  printf("%dx%d\n", d->aquarium_width, d->aquarium_height);
  for (int i = 0; i < d->nb_display; i++) {
    printf("%s %dx%d+%d+%d\n", d->display[i]->id, d->display[i]->vue_x,
           d->display[i]->vue_y, d->display[i]->vue_width,
           d->display[i]->vue_height);
  }
}

void add_view(display_aquarium *d, char *id, char *vue_x, char *vue_y,
              char *vue_width, char *vue_height) {
  d->nb_display++;
  d->display[d->nb_display] = malloc(sizeof(struct display));
  d->display[d->nb_display]->id = id;
  d->display[d->nb_display]->vue_x = *(int *)vue_x;
  d->display[d->nb_display]->vue_y = *(int *)vue_y;
  d->display[d->nb_display]->vue_width = *(int *)vue_width;
  d->display[d->nb_display]->vue_height = *(int *)vue_height;
}

void delete_view(display_aquarium *d, int id) {
  d->display[id] = NULL;
  d->nb_display--;
}