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
    tex->width = 32;
    tex->height = 16;

    Transform* player_transform = transform_get(player);
    float player_x = player_transform->pos_x;
    float player_y = player_transform->pos_y;

    EntityID projectile = entity_create();
    transform_set(projectile, player_x + 64, player_y, 0, 0, 300.0f, 0);
    collider_set(projectile, 0, 0, 32, 16, false);
    tag_set(projectile, TAG_PROJECTILE);
    sprite_add_layer(projectile, tex, 0, 0, true);
}