//
// Created by Ahmet Eren Kutsal on 9.07.2025.
//

#include "player.h"
#include "../include/ecs/components/component_transform.h"
#include "../include/ecs/components/component_sprite.h"
#include "../include/ecs/components/component_collider.h"
#include "../include/ecs/components/component_tag.h"
#include "../include/renderer.h"

void player_attack(EntityID player)
{
    Texture* tex = renderer_load_texture("assets/player.png");
    if (!tex) {
        fprintf(stderr, "Failed to load player texture!\n");
        return;
    }
    tex->width = 16;
    tex->height = 8;

    Transform* player_transform = transform_get(player);
    float player_x = player_transform->pos_x;
    float player_y = player_transform->pos_y;

    const Vec2f velocity = vec2f(player_transform->dx, player_transform->dy);
    float vel_x = velocity.x * 3;
    float vel_y = velocity.y * 3;

    Vec2f projectile_speed = vec2f(vel_x, vel_y);
    Vec2f normalized_p_speed = vec2f_mul(vec2f_normalize(projectile_speed), 300.0f);

    EntityID projectile = entity_create();
    if (vel_x > 0)
    {
        transform_set(projectile, player_x + 48, player_y, 0, 0, normalized_p_speed.x, normalized_p_speed.y);
    } else if (vel_x < 0)
    {
        transform_set(projectile, player_x - 48, player_y, 0, 0, normalized_p_speed.x, normalized_p_speed.y);
    } else
    {
        transform_set(projectile, player_x + 48, player_y, 0, 0, normalized_p_speed.x, normalized_p_speed.y);
    }
    //transform_set(projectile, player_x + 48, player_y, 0, 0, 300.0f, 0);
    collider_set(projectile, 0, 0, 32, 16, false);
    tag_set(projectile, TAG_PROJECTILE);
    sprite_add_layer(projectile, tex, 0, 0, true);
}