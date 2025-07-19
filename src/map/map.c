//
// Created by Ahmet Eren Kutsal on 16.07.2025.
//

#include "../../include/map/map.h"

#include <stdio.h>
#include <stdlib.h>

static Map* current_map = NULL;

void map_set(Map* map)
{
    current_map = map;
}

Map* map_get()
{
    return current_map;
}

Map* map_create(int width, int height, Tileset* tileset) {
    Map* map = malloc(sizeof(Map));
    if (!map) return NULL;

    map->width = width;
    map->height = height;
    map->tileset = tileset;
    map->tiles = malloc(sizeof(Tile) * width * height);
    if (!map->tiles) {
        free(map);
        return NULL;
    }

    return map;
}


void map_free(Map* map)
{
    if (!map) return;

    free(map->tiles);
    map->tiles = NULL;
}

void map_set_tile(Map* m, Tile tile, int x, int y)
{
    m->tiles[y * m->width + x] = tile;
}

/*
 * (0,0) (0,1)
 * (1,0) (1,1)
 */
Tile* map_get_tile(Map* m, int x, int y)
{
    return &m->tiles[y * m->width + x];
}