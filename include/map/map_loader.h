//
// Created by Ahmet Eren Kutsal on 16.07.2025.
//

#ifndef MAP_LOADER_H
#define MAP_LOADER_H

#include "map.h"

Map load_map(char* filename);
void unload_map(Map* map);

#endif //MAP_LOADER_H
