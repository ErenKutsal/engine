//
// Created by Ahmet Eren Kutsal on 21.07.2025.
//

#include "../../../include/ecs/components/component_script.h"
#include <stdbool.h>

static ScriptComponent scripts[MAX_ENTITIES];
static bool has_script[MAX_ENTITIES];

void script_init()
{
    memset(scripts, 0, sizeof(scripts));
    memset(has_script, 0, sizeof(has_script));
}

void script_enable(EntityID id)
{
    if (id.index >= MAX_ENTITIES) return;

    has_script[id.index] = true;
}

void script_set_collision(EntityID id, CollisionCallback on_collision)
{
    if (id.index >= MAX_ENTITIES) return;

    scripts[id.index].on_collision = on_collision;
}

ScriptComponent script_get(EntityID id)
{
    if (id.index >= MAX_ENTITIES || !has_script[id.index]) return (ScriptComponent) {0};

    return scripts[id.index];
}

bool script_has(EntityID id)
{
    return id.index < MAX_ENTITIES && has_script[id.index];
}

void script_clear(EntityID id)
{
    if (id.index >= MAX_ENTITIES) return;

    scripts[id.index] = (ScriptComponent) {0};
    has_script[id.index] = false;
}