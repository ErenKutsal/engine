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

void movement_update(const float delta_time)
{
    for (int i = 0; i < MAX_ENTITIES; i++)
    {
        EntityID id1 = (EntityID) {i, entity_get_generation(i)};
        if (!transform_has(id1) || !entity_is_alive(id1) || !collider_has(id1))
        {
            continue;
        }
        predict_update(id1);
        Transform* t1 = transform_get(id1);
        Collider* c1 = collider_get(id1);
        AABB aabb1x = {t1->pos_x + c1->offset_x + t1->dx * delta_time,
                       t1->pos_y + c1->offset_y,
                       c1->width,
                       c1->height};
        AABB aabb1y = {t1->pos_x + c1->offset_x,
                       t1->pos_y + c1->offset_y + t1->dy * delta_time,
                       c1->width,
                       c1->height};
        for (int j = 0; j < MAX_ENTITIES; j++)
        {
            if (i == j) continue;

            EntityID id2 = (EntityID) {j, entity_get_generation(j)};
            if (!collider_has(id2) || !transform_has(id2) || !entity_is_alive(id2))
            {
                continue;
            }

            Transform* t2 = transform_get(id2);
            Collider* c2 = collider_get(id2);
            if (c2->is_trigger) continue;

            AABB aabb2 = {t2->pos_x + c2->offset_x,
                          t2->pos_y + c2->offset_y,
                          c2->width,
                          c2->height};
            if (aabb_intersect_rect(aabb1x, aabb2))
            {
                //entity will collide if it moves horizontally
                printf("hit!\n");
                t1->dx = 0;
            }
            if (aabb_intersect_rect(aabb1y, aabb2))
            {
                printf("hit!\n");
                t1->dy = 0;
            }
        }
        Vec2f velocity = vec2f(t1->dx, t1->dy);
        Vec2f normalized_vel = vec2f_mul(vec2f_normalize(velocity), vec2f_length(t1->vel) * delta_time);
        if (vec2f_near_zero(normalized_vel)) normalized_vel = VEC2F_ZERO;
        t1->pos_x += normalized_vel.x;
        t1->pos_y += normalized_vel.y;
    }
}

void predict_update(EntityID id)
{
    if (tag_has(id, TAG_NONE)) return;

    if (tag_has(id, TAG_PLAYER))
    {
        player_request_update(id, input_get(id));
    } else if (tag_has(id, TAG_ENEMY))
    {
        //TODO implement ai
    } else if (tag_has(id, TAG_PROJECTILE))
    {
        projectile_request_update(id);
    }
}

void player_request_update(EntityID player, Input* input)
{
    Transform* t = transform_get(player);
    float dx = 0;
    float dy = 0;
    if (input->move_right) dx += t->vel.x;
    if (input->move_left) dx -= t-> vel.x;
    if (input->move_up) dy -= t->vel.y;
    if (input->move_down) dy += t->vel.y;

    t->dx = dx;
    t->dy = dy;
}

void projectile_request_update(EntityID projectile)
{
    Transform* t = transform_get(projectile);
    t->dx = t->vel.x;
    t->dy = t->vel.y;
}