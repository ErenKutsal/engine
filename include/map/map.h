//
// Created by Ahmet Eren Kutsal on 16.07.2025.
//

#ifndef MAP_H
#define MAP_H

#include <SDL_render.h>
#include <stdbool.h>
#include "../renderer.h"

#define MYFILENAME_MAX 128
#define TILE_ATTRIBUTES_MAX 64
#define ENTITY_DATAS_MAX 64

typedef struct
{
    int index;
    bool is_passable;
} TileAttribute;

#define TILE_INVALID (TileAttribute) {.index = -1, .is_passable = true}

typedef struct {
    char type[32];
    int x, y;
} EntityData;

typedef struct
{
    char filename[MYFILENAME_MAX];
    Texture* texture;
    int cols, rows;
} Tileset;

typedef struct
{
    TileAttribute* tile_attributes;
    int tile_attr_count;

    EntityData* entity_datas;
    int entity_data_count;

    int map_width, map_height;
    int tile_width, tile_height;
    Tileset* tileset;
    int* map_data;
} Map;

//Map* map_create(int width, int height, Tileset* tileset);
void map_free(Map* map);
void map_set_tile(Map* map, TileAttribute tile, int x, int y);
TileAttribute map_get_tile(Map* m, int x, int y);
void map_set(Map* map);
Map* map_get();


#endif //MAP_H
