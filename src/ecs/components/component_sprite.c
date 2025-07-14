//
// Created by Ahmet Eren Kutsal on 11.07.2025.
//

#include "../../../include/ecs/components/component_sprite.h"

#include "string.h"

static Sprite sprites[MAX_ENTITIES];

void sprite_init()
{
    memset(sprites, 0, sizeof(sprites));
}

int sprite_add_layer(EntityID id, Texture* tex, int offset_x, int offset_y, bool visible)
{
    if (id.index >= MAX_ENTITIES) return 0;

    Sprite* sprite = &sprites[id.index];

    if (sprite->count >= MAX_SPRITE_LAYERS) return 0;

    sprite->layers[sprite->count] = (SpriteLayer) {tex, offset_x, offset_y, visible};
    sprite->count++;
    return 1;
}

void sprite_set_layer_visible(EntityID id, int layer_index, bool visible)
{
    if (id.index >= MAX_ENTITIES || layer_index >= sprites[id.index].count) return;

    sprites[id.index].layers[layer_index].visible = visible;
}

Sprite* sprite_get(EntityID id)
{
    if (id.index >= MAX_ENTITIES) return NULL;

    return &sprites[id.index];
}

void sprite_clear(EntityID id)
{
    if (id.index >= MAX_ENTITIES) return;

    memset(sprites[id.index].layers, 0, sizeof(sprites[id.index].layers));
    sprites[id.index].count = 0;
}
