//
// Created by Ahmet Eren Kutsal on 12.07.2025.
//

#include "../../../include/ecs/systems/system_movement.h"

#include <stdio.h>
#include <string.h>

#include "../../../include/ecs/systems/system_collision.h"
#include "../../../include/ecs/entity.h"
#include "../../../include/ecs/components/component_transform.h"
#include "../../../include/ecs/components/component_input.h"
#include "../../../include/ecs/components/component_tag.h"
#include "../../../include/ecs/components/component_collider.h"
#include "../../../include/my_math.h"
#include "../../../include/ecs/components/component_script.h"

void movement_update(const float delta_time)
{
    for (int i = 0; i < MAX_ENTITIES - 1; i++)
    {
        EntityID id1 = (EntityID) {i, entity_get_generation(i)};
        if (!transform_has(id1) || !entity_is_alive(id1) || !collider_has(id1))
        {
            continue;
        }
        Transform* t1 = transform_get(id1);
        Vec2f delta_vector = predict_update(id1);
        t1->dx = delta_vector.x;
        t1->dy = delta_vector.y;

        Collider* c1 = collider_get(id1);
        CollisionInfo collision_info = check_entity_tile_collision(id1, map_get(), delta_time);
        if (collision_info.collided)
        {
            switch (collision_info.direction)
            {
                case DIRECTION_HORIZONTAL | DIRECTION_VERTICAL:
                    t1->dx = 0;
                    t1->dy = 0;
                    break;
                case DIRECTION_HORIZONTAL:
                    t1->dx = 0;
                    break;
                case DIRECTION_VERTICAL:
                    t1->dy = 0;
                    break;
                default: ;
            }
        }

        const AABB aabb1x = {t1->pos_x + c1->offset_x + t1->dx * 2 *delta_time,
                       t1->pos_y + c1->offset_y,
                       c1->width,
                       c1->height};
        const AABB aabb1y = {t1->pos_x + c1->offset_x,
                       t1->pos_y + c1->offset_y + t1->dy * 2 * delta_time,
                       c1->width,
                       c1->height};
        for (int j = i + 1; j < MAX_ENTITIES; j++)
        {
            if (i == j) continue;

            const EntityID id2 = (EntityID) {j, entity_get_generation(j)};
            if (!entity_is_alive(id2) || !collider_has(id2) || !transform_has(id2)) continue;

            Transform* t2 = transform_get(id2);
            Collider* c2 = collider_get(id2);
            if (c2->is_trigger) continue;

            AABB aabb2 = {t2->pos_x + c2->offset_x,
                          t2->pos_y + c2->offset_y,
                          c2->width,
                          c2->height};
            if (aabb_intersect_rect(aabb1x, aabb2))
            {
                if (script_get(id1).on_collision)
                {
                    script_get(id1).on_collision(id1, id2, DIRECTION_HORIZONTAL);
                }
                else
                {
                    collide_entities(id1, id2, DIRECTION_HORIZONTAL); //changes entities' transforms
                }
            }
            if (aabb_intersect_rect(aabb1y, aabb2))
            {
                if (script_get(id1).on_collision)
                {
                    script_get(id1).on_collision(id1, id2, DIRECTION_VERTICAL);
                }
                else
                {
                    collide_entities(id1, id2, DIRECTION_VERTICAL); //changes entities' transforms
                }
            }
        }
        const Vec2f velocity = vec2f(t1->dx, t1->dy);
        Vec2f normalized_vel = vec2f_mul(vec2f_normalize(velocity), vec2f_length(t1->vel) * delta_time);
        if (vec2f_near_zero(normalized_vel)) normalized_vel = VEC2F_ZERO;

        t1->pos_x += normalized_vel.x;
        t1->pos_y += normalized_vel.y;
    }
}

static Vec2f predict_update(EntityID id)
{
    if (tag_has(id, TAG_NONE)) return VEC2F_ZERO;

    if (tag_has(id, TAG_PLAYER))
    {
        return player_request_update(id, input_get(id));
    } else if (tag_has(id, TAG_ENEMY))
    {
        return VEC2F_ZERO;
        //TODO implement ai
    } else if (tag_has(id, TAG_PROJECTILE))
    {
        return projectile_request_update(id);
    }
    return VEC2F_ZERO;
}

static Vec2f player_request_update(EntityID player, Input* input)
{
    Transform* t = transform_get(player);
    float dx = 0;
    float dy = 0;
    if (input->move_right) dx = t->vel.x;
    if (input->move_left) dx = -t-> vel.x;
    if (input->move_up) dy = -t->vel.y;
    if (input->move_down) dy = t->vel.y;

    return vec2f(dx, dy);
}

static Vec2f projectile_request_update(EntityID projectile)
{
    Transform* t = transform_get(projectile);
    return vec2f(t->vel.x, t->vel.y);
}