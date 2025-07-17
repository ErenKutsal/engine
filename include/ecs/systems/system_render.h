//
// Created by Ahmet Eren Kutsal on 12.07.2025.
//

#ifndef SYSTEM_RENDER_H
#define SYSTEM_RENDER_H

#include "../../map/map.h"
#include "../../../include/camera.h"

void system_render_draw_all(Map* map);
void system_render_draw_map(Map* map,Camera cam, SDL_Renderer* renderer);

#endif //SYSTEM_RENDER_H
