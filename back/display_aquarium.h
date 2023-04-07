#ifndef DISPLAY_AQUARIUM_H
#define DISPLAY_AQUARIUM_H

#define MAX_DISPLAY 5

typedef struct display {
  char *id;
  int vue_x;
  int vue_y;
  int vue_width;
  int vue_height;
} display;

typedef struct display_aquarium {
  int nb_display;
  int aquarium_width;
  int aquarium_height;
  display *display[MAX_DISPLAY];
} display_aquarium;

void load_aquarium(display_aquarium *d, char *file_name);
void save_aquarium(display_aquarium *d, char *file_name);
void show_aquarium(display_aquarium *d);
void add_view(display_aquarium *d, char *id, char *vue_x, char *vue_y,
              char *vue_width, char *vue_height);
void delete_view(display_aquarium *d, int id);

#endif