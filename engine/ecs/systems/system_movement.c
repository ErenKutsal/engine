//
// Created by Ahmet Eren Kutsal on 12.07.2025.
//

#include "system_movement.h"

#include <stdio.h>
#include <string.h>

#include "system_collision.h"
#include "../entity.h"
#include "../components/component_transform.h"
#include "../components/component_input.h"
#include "../components/component_tag.h"
#include "../components/component_collider.h"

/*
void movement_update(const float delta_time)
{
    for (int i = 0; i < MAX_ENTITIES; i++)
    {
        EntityID id = {i, entity_get_generation(i)};
        Transform* t = transform_get(id);
        if (!t) continue;

        t->pos_x += t->dx * delta_time;
        t->pos_y += t->dy * delta_time;
    }
}
*/

void movement_update(const float delta_time)
{
    bool entity_intersects_x[MAX_ENTITIES];
    bool entity_intersects_y[MAX_ENTITIES];
    memset(entity_intersects_x, 0, sizeof(entity_intersects_x));
    memset(entity_intersects_y, 0, sizeof(entity_intersects_y));
    for (int i = 0; i < MAX_ENTITIES; i++)
    {
        EntityID id1 = {i, entity_get_generation(i)};
        if (!entity_is_alive(id1)) continue;

        Transform* t1 = transform_get(id1);
        if (!t1) continue;

        if (tag_has(id1, TAG_PLAYER))
        {
            player_request_update(id1, input_get(id1));
        }

        Collider* c1 = collider_get(id1);
        if (!c1 || c1->is_trigger) continue;

        AABB aabb1x = {t1->pos_x + c1->offset_x + t1->dx * delta_time, t1->pos_y + c1->offset_y, c1->width, c1->height};
        AABB aabb1y = {t1->pos_x + c1->offset_x, t1->pos_y + c1->offset_y + t1->dy * delta_time, c1->width, c1->height};
        bool can_move_horizontally = true;
        bool can_move_vertically = true;
        for (int j = 0; j < MAX_ENTITIES; j++)
        {
            if (j == i) continue;

            EntityID id2 = {j, entity_get_generation(j)};
            if (!entity_is_alive(id2)) continue;

            Transform* t2 = transform_get(id2);
            if (!t2) continue;

            Collider* c2 = collider_get(id2);
            if (!c2 || c2->is_trigger) continue;

            AABB aabb2 = {t2->pos_x + c2->offset_x, t2->pos_y + c2->offset_y, c2->width, c2->height};
            if (aabb_intersect_rect(aabb1x, aabb2))
            {
                printf("hit!");
                can_move_horizontally = false;
                entity_intersects_x[j] = true;
                t1->dx = 0;
            }
            if (aabb_intersect_rect(aabb1y, aabb2))
            {
                printf("hit!");
                can_move_vertically = false;
                entity_intersects_y[j] = true;
                t1->dy = 0;
            }
        }
        //if (!can_move_horizontally) t1->dx = 0;
        //if (!can_move_vertically) t1->dy = 0;
        t1->pos_x += t1->dx;
        t1->pos_y += t1->dy;
    }
}

void player_request_update(EntityID player, Input* input)
{
    Transform* t = transform_get(player);
    float dx = 0;
    float dy = 0;
    if (input->move_right) dx += t->vel;
    if (input->move_left) dx -= t-> vel;
    if (input->move_up) dy -= t->vel;
    if (input->move_down) dy += t->vel;

    transform_set(player, t->pos_x, t->pos_y, dx, dy, t->vel);
}