//
// Created by Ahmet Eren Kutsal on 16.07.2025.
//

#ifndef MAP_H
#define MAP_H

#include <SDL_render.h>
#include <stdbool.h>
#include "../renderer.h"

typedef struct
{
    int index;
    int size;
    bool is_passable;
} Tile;

typedef struct
{
    char* filename;
    Texture* texture;
    int cols, rows;
    int tile_size;
} Tileset;

typedef struct
{
    Tile* tiles;
    int width, height;
    Tileset* tileset;
} Map;

Map* map_create(int width, int height, Tileset* tileset);
void map_free(Map* map);
void map_set_tile(Map* map, Tile tile, int x, int y);
Tile* map_get_tile(Map* m, int x, int y);
void map_set(Map* map);
Map* map_get();


#endif //MAP_H
