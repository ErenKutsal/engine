//
// Created by Ahmet Eren Kutsal on 12.07.2025.
//

#include "../../../include/ecs/systems/system_input.h"
#include "../../../include/ecs/entity.h"
#include "../../../include/ecs/components/component_input.h"
#include "../../../include/key_binding.h"

void system_input_update(const Uint8* keyboard_state)
{
    for (int i = 0; i < MAX_ENTITIES; i++)
    {
        EntityID id = {i, entity_get_generation(i)};
        if (!input_has(id)) continue;

        Input input = {0};
        input.move_up    = keyboard_state[SDL_SCANCODE_W];
        input.move_down  = keyboard_state[SDL_SCANCODE_S];
        input.move_left  = keyboard_state[SDL_SCANCODE_A];
        input.move_right = keyboard_state[SDL_SCANCODE_D];
        input.shoot      = keyboard_state[SDL_SCANCODE_SPACE];
        input_set(id, input);
    }

    binding_update(keyboard_state);
}