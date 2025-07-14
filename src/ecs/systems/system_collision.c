//
// Created by Ahmet Eren Kutsal on 12.07.2025.
//

#include "../../../include/ecs/systems/system_collision.h"
#include "../../../include/ecs/components/component_transform.h"

bool aabb_intersect_rect(AABB a, AABB b)
{
    return !(a.y + a.h <= b.y ||
             a.x + a.w <= b.x ||
             b.y + b.h <= a.y ||
             b.x + b.w <= a.x);
}

void collide_entities(EntityID id1, EntityID id2)
{
    if (tag_has(id1, TAG_ENEMY | TAG_PLAYER))
    {
        if (tag_has(id2, TAG_PROJECTILE))
        {
            transform_get(id1)->dx += 10;
            entity_destroy(id2);
        }
    } else if (tag_has(id2, TAG_ENEMY | TAG_PLAYER))
    {
        if (tag_has(id1, TAG_PROJECTILE))
        {
            transform_get(id2)->dx += 10;
            entity_destroy(id1);
        }
    }
}