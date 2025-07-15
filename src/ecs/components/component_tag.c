//
// Created by Ahmet Eren Kutsal on 12.07.2025.
//

#include "../../../include/ecs/components/component_tag.h"
#include "../../../include/ecs/entity.h"

#include <stdint.h>
#include <string.h>

static Tag tags[MAX_ENTITIES];
static bool has_tag[MAX_ENTITIES];

void tag_init()
{
    memset(tags, 0, sizeof(tags));
    memset(has_tag, 0, sizeof(has_tag));
}
void tag_set(EntityID id, uint32_t flags)
{
    if (id.index >= MAX_ENTITIES) return;

    tags[id.index].flags = flags;
    has_tag[id.index] = true;
}

void tag_add(EntityID id, uint32_t flags)
{
    if (id.index >= MAX_ENTITIES) return;

    tags[id.index].flags |= flags;
}

void tag_remove(EntityID id, uint32_t flags)
{
    if (id.index >= MAX_ENTITIES) return;

    tags[id.index].flags &= ~flags;
}

bool tag_has(EntityID id, uint32_t flag)
{
    if (id.index >= MAX_ENTITIES || !has_tag[id.index]) return false;

    return (tags[id.index].flags & flag) != 0;
}

Tag* tag_get(EntityID id)
{
    if (id.index >= MAX_ENTITIES || !has_tag[id.index]) return NULL;

    return &tags[id.index];
}

void tag_clear(EntityID id)
{
    if (id.index >= MAX_ENTITIES) return;

    tags[id.index].flags = 0;
    has_tag[id.index] = false;
}

bool is_player(EntityID id)     { return tag_has(id, TAG_PLAYER); }
bool is_enemy(EntityID id)      { return tag_has(id, TAG_ENEMY); }
bool is_projectile(EntityID id) { return tag_has(id, TAG_PROJECTILE); }
