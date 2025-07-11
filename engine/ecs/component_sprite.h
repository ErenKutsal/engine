//
// Created by Ahmet Eren Kutsal on 11.07.2025.
//

#ifndef COMPONENT_SPRITE_H
#define COMPONENT_SPRITE_H

#include "../renderer.h"
#include "entity.h"

#include "stdbool.h"

#define MAX_SPRITE_LAYERS 4

typedef struct
{
    Texture* tex;
    int offset_x, offset_y;
    bool visible;
} SpriteLayer;

typedef struct
{
    SpriteLayer layers[MAX_SPRITE_LAYERS];
    int count; //how many layers that sprite has, not the index.
} Sprite;

void sprite_init();
int sprite_add_layer(EntityID id, Texture* tex, int offset_x, int offset_y, bool visible);
void sprite_set_layer_visible(EntityID id, int layer_index, bool visible);
Sprite* sprite_get(EntityID id);
void sprite_clear(EntityID id);

#endif //COMPONENT_SPRITE_H
