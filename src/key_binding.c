//
// Created by Ahmet Eren Kutsal on 14.07.2025.
//

#include "../include/key_binding.h"

static KeyBinding bindings[MAX_BINDINGS];
static bool on_hold[MAX_BINDINGS];
static int binding_count;

void key_binding_init()
{
    memset(bindings, 0, sizeof(bindings));
    binding_count = 0;
}


void bind_key(SDL_Scancode key, ActionCallback callback, const char* name, EntityID id)
{
    if (id.index > MAX_ENTITIES || binding_count >= MAX_BINDINGS) return;

    bindings[binding_count] = (KeyBinding) {
        .key = key,
        .callback = callback,
        .name = name,
        .id = id};
    binding_count++;
}

void binding_update(const Uint8* keyboard_state)
{
    for (int i = 0; i < binding_count; i++)
    {
        KeyBinding binding = bindings[i];
        if (keyboard_state[binding.key])
        {
            if (on_hold[i]) continue;
            binding.callback(binding.id);
            on_hold[i] = true;
        } else
        {
            on_hold[i] = false;
        }
    }
}