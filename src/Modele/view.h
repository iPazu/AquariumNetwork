//
// Created by Axel PETIT on 12/04/2023.
//

#ifndef AQUARIUM_NETWORK_VIEW_H
#define AQUARIUM_NETWORK_VIEW_H

typedef struct view {
    int id;
    int x;
    int y;
    int width;
    int height;
} view;

view *init_view(int id, int x, int y, int width, int height);

void show_view(view *v);

#endif //AQUARIUM_NETWORK_VIEW_H
