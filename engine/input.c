//
// Created by Ahmet Eren Kutsal on 9.07.2025.
//

#include "input.h"

#include <SDL_events.h>
#include <SDL_scancode.h>
#include <stdbool.h>

static bool input_keys[SDL_NUM_SCANCODES];
static bool quit_requested = false;

void input_update()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            quit_requested = true;
        }
        if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
        {
            input_keys[event.key.keysym.scancode] = SDL_KEYDOWN;
        }
    }
}

bool input_is_down(SDL_Scancode sc)
{
    return input_keys[sc];
}

bool input_should_quit()
{
    return quit_requested;
}