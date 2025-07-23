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
/*
Map* map_create(int width, int height, Tileset* tileset) {
    Map* map = malloc(sizeof(Map));
    if (!map) return NULL;

    map->width = width;
    map->height = height;
    map->tileset = tileset;
    map->tile_attributes = malloc(sizeof(TileAttribute));
    if (!map->tiles) {
        free(map);
        return NULL;
    }

    return map;
}
*/

void map_free(Map* map)
{
    if (!map) return;

    free(map->tile_attributes);
    free(map->entity_datas);
    free(map->map_data);
    if (map->tileset)
    {
        SDL_DestroyTexture(map->tileset->texture->texture);
        free(map->tileset->texture);
        free(map->tileset);
    }
    map->tile_attributes = NULL;
    map->entity_datas = NULL;
    map->map_data = NULL;
    map->tileset = NULL;
}

void map_set_tile(Map* map, TileAttribute tile, int x, int y)
{
    map->map_data[y * map->map_width + x] = tile.index;
}

TileAttribute map_get_tile(Map* map, int x, int y)
{
    int index = map->map_data[y * map->map_width + x];
    return map->tile_attributes[index];
}