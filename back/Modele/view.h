//
// Created by Axel PETIT on 12/04/2023.
//

#ifndef AQUARIUM_NETWORK_VIEW_H
#define AQUARIUM_NETWORK_VIEW_H

typedef struct view {
    int id;
    int height;
    int width;
    int x;
    int y;
} view;

/**
 * @brief Create a view from a file
 * @param file
 * @return
 */
view *create_view_from_file(FILE *file);

view *create_view(int id, int x, int y, int width, int height);

#endif //AQUARIUM_NETWORK_VIEW_H
