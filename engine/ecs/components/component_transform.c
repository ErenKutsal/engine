//
// Created by Ahmet Eren Kutsal on 11.07.2025.
//

#include "../../../include/ecs/components/component_transform.h"
#include "../../../include/my_math.h"

#include <string.h>

static Transform transforms[MAX_ENTITIES];
static bool has_transform[MAX_ENTITIES];

void transform_init()
{
    memset(transforms, 0, sizeof(transforms));
    memset(has_transform, 0, sizeof(has_transform));
}

void transform_set(EntityID id, float pos_x, float pos_y, float dx, float dy, float vel_x, float vel_y)
{
    if (id.index >= MAX_ENTITIES) return;

    transforms[id.index] = (Transform) {pos_x, pos_y, dx, dy, vec2f(vel_x, vel_y)};
    has_transform[id.index] = true;
}

Transform* transform_get(EntityID id)
{
    if (id.index >= MAX_ENTITIES || !has_transform[id.index]) return NULL;

    return &transforms[id.index];
}

void transform_clear(EntityID id)
{
    if (id.index >= MAX_ENTITIES) return;

    memset(&transforms[id.index], 0, sizeof(Transform));
    has_transform[id.index] = false;
}

bool transform_has(EntityID id)
{
    return id.index < MAX_ENTITIES && has_transform[id.index];
}