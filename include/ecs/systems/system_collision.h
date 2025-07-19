//
// Created by Ahmet Eren Kutsal on 12.07.2025.
//

#ifndef SYSTEM_COLLISION_H
#define SYSTEM_COLLISION_H

#include <stdbool.h>
#include "../entity.h"
#include "../components/component_tag.h"
#include "../../map/map.h"

typedef enum
{
    DIRECTION_VERTICAL = 1 << 0,
    DIRECTION_HORIZONTAL = 1 << 1
} CollisionDirection;

typedef struct
{
    uint8_t direction;
} Direction;

typedef struct
{
    float x, y, w, h;
} AABB;

bool aabb_intersect_rect(AABB a, AABB b);
void collide_entities(EntityID id1, EntityID id2, uint8_t direction);

//private helper functions
static void on_projectile_hit(EntityID id);
static void resolve_entity_collision(EntityID id1, EntityID id2, uint8_t direction);
void resolve_entity_tile_collision(EntityID id, Map* map);

#endif //SYSTEM_COLLISION_H
