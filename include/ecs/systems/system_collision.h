//
// Created by Ahmet Eren Kutsal on 12.07.2025.
//

#ifndef SYSTEM_COLLISION_H
#define SYSTEM_COLLISION_H

#include <stdbool.h>
#include "../entity.h"
#include "../components/component_tag.h"

typedef struct
{
    float x, y, w, h;
} AABB;

bool aabb_intersect_rect(AABB a, AABB b);
void collide_entities(EntityID id1, EntityID id2);
#endif //SYSTEM_COLLISION_H
