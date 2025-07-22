//
// Created by Ahmet Eren Kutsal on 21.07.2025.
//

#ifndef COMPONENT_SCRIPT_H
#define COMPONENT_SCRIPT_H

#include "../entity.h"
#include "../systems/system_collision.h"

typedef void (*CollisionCallback) (EntityID self, EntityID other, CollisionDirection direction);

typedef struct
{
    CollisionCallback on_collision;
} ScriptComponent;

void script_init();
void script_enable(EntityID id);
void script_set_collision(EntityID id, CollisionCallback on_collision);
ScriptComponent script_get(EntityID id);
bool script_has(EntityID id);
void script_clear(EntityID id);

#endif //COMPONENT_SCRIPT_H
