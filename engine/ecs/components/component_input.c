//
// Created by Ahmet Eren Kutsal on 12.07.2025.
//

#include "../../../include/ecs/components/component_input.h"

#include <string.h>

static Input inputs[MAX_ENTITIES];
static bool has_input[MAX_ENTITIES];

void input_init()
{
    memset(inputs, 0, sizeof(inputs));
    memset(has_input, 0, sizeof(has_input));
}

void input_enable(EntityID id)
{
    if (id.index >= MAX_ENTITIES) return;

    has_input[id.index] = true;
}

void input_set(EntityID id, Input input)
{
    if (id.index >= MAX_ENTITIES) return;

    inputs[id.index] = input;
    has_input[id.index] = true;
}

Input* input_get(EntityID id)
{
    if (id.index >= MAX_ENTITIES || !has_input[id.index]) return NULL;

    return &inputs[id.index];
}
void input_clear(EntityID id)
{
    if (id.index >= MAX_ENTITIES) return;

    memset(&inputs[id.index], 0, sizeof(Input));
    has_input[id.index] = false;
}
bool input_has(EntityID id)
{
    return id.index < MAX_ENTITIES && has_input[id.index];
}