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

void collide_entities(EntityID id1, EntityID id2, uint8_t direction)
{
    // Projectile hits player or enemy
    if (is_projectile(id1) && (is_enemy(id2) || is_player(id2))) {
        on_projectile_hit(id2);
        entity_destroy(id1);
        return;
    }
    if (is_projectile(id2) && (is_enemy(id1) || is_player(id1))) {
        on_projectile_hit(id1);
        entity_destroy(id2);
        return;
    }

    // Player or enemy hits another player or enemy
    if ((is_enemy(id1) || is_player(id1)) && (is_enemy(id2) || is_player(id2))) {
        resolve_entity_collision(id1, id2, direction);
    }
}

static void on_projectile_hit(EntityID id)
{
    transform_get(id)->pos_x += 10;
}


static void resolve_entity_collision(EntityID id1, EntityID id2, uint8_t direction)
{
    if (!(direction & ~DIRECTION_HORIZONTAL))
    {
        transform_get(id1)->dx = 0;
        transform_get(id2)->dx = 0;
    } else if (!(direction & ~DIRECTION_VERTICAL))
    {
        transform_get(id1)->dy = 0;
        transform_get(id2)->dy = 0;
    }
}