//
// Created by Ahmet Eren Kutsal on 15.07.2025.
//

#ifndef CAMERA_H
#define CAMERA_H

#include "ecs/entity.h"

typedef struct
{
    float x, y;
    float width, height;
    EntityID target;
} Camera;

void camera_init(float width, float height);
void camera_set_target(EntityID id);
void camera_update(float delta_time);
Camera camera_get();

#endif //CAMERA_H
