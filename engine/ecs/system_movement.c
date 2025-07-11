//
// Created by Ahmet Eren Kutsal on 12.07.2025.
//

#include "system_movement.h"
#include "entity.h"
#include "component_transform.h"

void movement_update(const float delta_time)
{
    for (int i = 0; i < MAX_ENTITIES; i++)
    {
        EntityID id = {i, entity_get_generation(i)};
        Transform* t = transform_get(id);
        if (!t) continue;

        t->pos_x += t->vel_x * delta_time;
        t->pos_y += t->vel_y * delta_time;
    }
}