//
// Created by Ahmet Eren Kutsal on 12.07.2025.
//

#include "../../../include/ecs/systems/system_collision.h"

#include "../../../include/camera.h"
#include "../../../include/engine.h"
#include "../../../include/ecs/components/component_collider.h"
#include "../../../include/ecs/components/component_transform.h"

bool aabb_intersect_rect(AABB a, AABB b)
{
    return !(a.y + a.h < b.y ||
             a.x + a.w < b.x ||
             b.y + b.h < a.y ||
             b.x + b.w < a.x);
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

CollisionInfo check_entity_tile_collision(EntityID id, Map* map, float delta_time)
{
    if (!transform_has(id) || !collider_has(id)) return COLLISION_INVALID;;

    int tile_width = map->tile_width;
    int tile_height = map->tile_height;
    Transform* t = transform_get(id);
    Collider* c = collider_get(id);
    int tile_x_start = (int)floorf((t->pos_x + c->offset_x) / (float)tile_width) - 1;
    int tile_y_start = (int)floorf((t->pos_y + c->offset_y) / (float)tile_height) - 1;
    int tile_x_end = (int)floorf((t->pos_x + c->offset_x + c->width) / (float)tile_width) + 1;
    int tile_y_end = (int)floorf((t->pos_y + c->offset_y + c->height) / (float)tile_height) + 1;

    AABB aabbx = {
        t->pos_x + c->offset_x + t->dx * 2 * delta_time,
        t->pos_y + c->offset_y,
        c->width,
        c->height
        };
    AABB aabby = {
        t->pos_x + c->offset_x,
        t->pos_y + c->offset_y + t->dy * 2 * delta_time,
        c->width,
        c->height
        };
    bool collided = false;
    bool collided_horizontally = false;
    bool collided_vertically = false;

    //Justin Case
    if (tile_x_start < 0 || tile_x_start > map->map_width || tile_y_start < 0 || tile_y_start > map->map_height)
    {
        return COLLISION_INVALID;
    }
    for (int i = tile_x_start; i <= tile_x_end; i++)
    {
        for (int j = tile_y_start; j <= tile_y_end; j++)
        {
            const TileAttribute tile = map_get_tile(map, i, j);
            const AABB tile_aabb = {
                .x = (float)i * (float)tile_width,
                .y = (float)j * (float)tile_height,
                .w = (float)tile_width,
                .h = (float)tile_height
                };
            if (aabb_intersect_rect(aabbx, tile_aabb))
            {
                if (!tile.is_passable)
                {
                    collided = true;
                    collided_horizontally = true;
                }
            }
            if (aabb_intersect_rect(aabby, tile_aabb))
            {
                if (!tile.is_passable)
                {
                    collided = true;
                    collided_vertically = true;
                }
            }
        }
    }
    if (collided)
    {
        if (collided_horizontally & !collided_vertically)
        {
            return (CollisionInfo) {collided, DIRECTION_HORIZONTAL};
        }
        if (collided_vertically & !collided_horizontally)
        {
            return (CollisionInfo) {collided, DIRECTION_VERTICAL};
        }
        if (collided_horizontally & collided_vertically)
        {
            return (CollisionInfo) {collided, DIRECTION_VERTICAL | DIRECTION_HORIZONTAL};
        }
    }
    return COLLISION_INVALID;
}

/*
// unused
void resolve_entity_tile_collision(EntityID id, Map* map)
{
    float delta_time = engine_delta_time();
    if (!transform_has(id) || !collider_has(id)) return;
    int tile_size = map->tiles->size;
    Transform* t = transform_get(id);
    Collider* c = collider_get(id);
    int tile_x_start = (int)floorf((t->pos_x + c->offset_x) / tile_size) - 1;
    int tile_y_start = (int)floorf((t->pos_y + c->offset_y) / tile_size) - 1;
    int tile_x_end = (int)floorf((t->pos_x + c->offset_x + c->width) / tile_size) + 1;
    int tile_y_end = (int)floorf((t->pos_y + c->offset_y + c->height) / tile_size) + 1;

    AABB aabbx = {t->pos_x + c->offset_x + t->dx * 2 * delta_time,
                       t->pos_y + c->offset_y,
                       c->width,
                       c->height};
    AABB aabby = {t->pos_x + c->offset_x,
                   t->pos_y + c->offset_y + t->dy * 2 * delta_time,
                   c->width,
                   c->height};
    for (int i = tile_x_start; i <= tile_x_end; i++)
    {
        for (int j = tile_y_start; j <= tile_y_end; j++)
        {
            Tile* tile = map_get_tile(map, i, j);
            AABB tile_aabb = {
                .x = i * tile_size,
                .y = j * tile_size,
                .w = tile_size,
                .h = tile_size
                };
            Camera cam = camera_get();
            SDL_Rect rect = {t->pos_x + c->offset_x + t->dx * 5 * delta_time - cam.x,
                       t->pos_y + c->offset_y - cam.y,
                       c->width,
                       c->height};

            // Set draw color (e.g., green)
            SDL_SetRenderDrawColor(engine_renderer(), 0, 255, 0, 255);

            // Draw rectangle outline for debug
            SDL_RenderDrawRect(engine_renderer(), &rect);
            if (aabb_intersect_rect(aabbx, tile_aabb))
            {
                if (!tile->is_passable)
                {
                    t->dx = 0;
                }
            }
            if (aabb_intersect_rect(aabby, tile_aabb))
            {
                if (!tile->is_passable)
                {
                    t->dy = 0;
                }
            }

        }
    }
}
*/
