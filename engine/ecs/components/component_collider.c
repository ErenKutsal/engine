//
// Created by Ahmet Eren Kutsal on 12.07.2025.
//

#include "component_collider.h"

#include <string.h>
#include <stdbool.h>

static Collider colliders[MAX_ENTITIES];
static bool has_collider[MAX_ENTITIES];

void collider_init()
{
    memset(colliders, 0, sizeof(colliders));
    memset(has_collider, 0, sizeof(has_collider));
}

int collider_set(EntityID id, float offset_x, float offset_y, float width, float height, bool is_trigger)
{
    if (id.index >= MAX_ENTITIES) return 0;

    colliders[id.index] = (Collider) {offset_x, offset_y, width, height, is_trigger};
    has_collider[id.index] = true;
    return 1;
}
void collider_set_trigger(EntityID id, bool is_trigger)
{
    if (id.index >= MAX_ENTITIES) return;

    colliders[id.index].is_trigger = is_trigger;
}


Collider* collider_get(EntityID id)
{
    if (id.index >= MAX_ENTITIES || !has_collider[id.index]) return NULL;

    return &colliders[id.index];
}

void collider_clear(EntityID id)
{
    if (id.index >= MAX_ENTITIES) return;

    memset(&colliders[id.index], 0, sizeof(Collider));
    has_collider[id.index] = false;
}

bool collider_has(EntityID id)
{
    return id.index < MAX_ENTITIES && has_collider[id.index];
}