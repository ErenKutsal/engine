//
// Created by Ahmet Eren Kutsal on 11.07.2025.
//

#ifndef COMPONENT_TRANSFORM_H
#define COMPONENT_TRANSFORM_H

#include "../entity.h"

typedef struct
{
    float pos_x;
    float pos_y;
    float dx;
    float dy;
    float vel;
} Transform;

void transform_init();
void transform_set(EntityID id, float pos_x, float pos_y, float dx, float dy, float vel);
Transform* transform_get(EntityID id);
void transform_clear(EntityID id);
bool transform_has(EntityID id);

#endif //COMPONENT_TRANSFORM_H
