#include "move.h"
#include <stdio.h>
#include <stdlib.h>

int check_position(int x, int y, int x_max, int y_max) {
  if (x < 0 || x > x_max || y < 0 || y > y_max) {
    return 0;
  }
  return 1;
}

void RandomPointWay(fish *f, int x_max_aquarium, int y_max_aquarium) {
  int x, y;
  do {
    x = rand() % (2 * f->speed);
    x = x - x / 2;
    y = rand() % (2 * f->speed);
    y = y - y / 2;
  } while (check_position(f->x + x, f->y + y, x_max_aquarium, y_max_aquarium) ==
           0);
  float rand1 = ((float)rand()/(float)(RAND_MAX/2))-1;
  float rand2 = ((float)rand()/(float)(RAND_MAX/2))-1;
  f->x = (rand1 > 0 ) ? f->x + x : f->x - x;
  f->y = (rand2 > 0 ) ? f->y + y : f->y - y;
  if (f->x < 0) {
    f->x = 0;
  }
  if (f->y < 0) {
    f->y = 0;
  }
  if (f->x > x_max_aquarium) {
    f->x = x_max_aquarium;
  }
  if (f->y > y_max_aquarium) {
    f->y = y_max_aquarium;
  }
}
void HorizontalWay(fish *f, int x_max_aquarium, int y_max_aquarium) {
  int x;
  do {
    x = rand() % (f->speed + 1);  // chose a number between 0 and speed
    x = rand() % 2 == 0 ? x : -x; // chose a direction
  } while (check_position(f->x + x, f->y, x_max_aquarium, y_max_aquarium) == 0);

  f->x = f->x + x;
}

void VerticalWay(fish *f, int x_max_aquarium, int y_max_aquarium) {
  int y;
  do {
    y = rand() % (f->speed + 1);  // chose a number between 0 and speed
    y = rand() % 2 == 0 ? y : -y; // chose a direction
  } while (check_position(f->x, f->y + y, x_max_aquarium, y_max_aquarium) == 0);

  f->y = f->y + y;
}