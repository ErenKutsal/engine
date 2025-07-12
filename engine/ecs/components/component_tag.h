//
// Created by Ahmet Eren Kutsal on 12.07.2025.
//

#ifndef COMPONENT_TAG_H
#define COMPONENT_TAG_H

#include "../entity.h"

#include <stdint.h>

typedef enum
{
    TAG_NONE = 0,
    TAG_PLAYER = 1 << 0,
    TAG_ENEMY = 1 << 1,
    TAG_STATIC = 1 << 2,
    TAG_TRIGGER = 1 << 3
} TagFlags;

typedef struct
{
    uint32_t flags;
} Tag;

void tag_init();
void tag_set(EntityID id, uint32_t flags);
void tag_add(EntityID id, uint32_t flags);
void tag_remove(EntityID id, uint32_t flags);
bool tag_has(EntityID id, uint32_t flag);
Tag* tag_get(EntityID id);
void tag_clear(EntityID id);

#endif //COMPONENT_TAG_H
