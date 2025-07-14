//
// Created by Ahmet Eren Kutsal on 14.07.2025.
//

#ifndef KEY_BINDING_H
#define KEY_BINDING_H

#define MAX_BINDINGS 128
#include <SDL_scancode.h>

#include "ecs/entity.h"

typedef void (*ActionCallback)(EntityID id);

typedef struct
{
    SDL_Scancode key;
    ActionCallback callback;
    const char* name;
    EntityID id;
} KeyBinding;

void key_binding_init();
void bind_key(SDL_Scancode key, ActionCallback callback, const char* name, EntityID id);
void binding_update(const Uint8* keyboard_state);

#endif //KEY_BINDING_H
