//
// Created by Ahmet Eren Kutsal on 12.07.2025.
//

#ifndef COMPONENT_COLLIDER_H
#define COMPONENT_COLLIDER_H

#include "../entity.h"

#include <stdbool.h>

typedef struct
{
    float offset_x, offset_y;
    float width, height;
    bool is_trigger;
} Collider;

void collider_init();
int collider_set(EntityID id, float offset_x, float offset_y, float width, float height, bool is_trigger);
void collider_set_trigger(EntityID id, bool is_trigger);
Collider* collider_get(EntityID id);
void collider_clear(EntityID id);

#endif //COMPONENT_COLLIDER_H
