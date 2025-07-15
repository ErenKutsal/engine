//
// Created by Ahmet Eren Kutsal on 9.07.2025.
//

#include "../include/engine.h"
#include "../include/renderer.h"
#include "../include/input.h"
#include "../include/ecs/ecs_init.h"
#include "../include/camera.h"

#include <SDL2/SDL.h>
#include <stdio.h>

static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;
static bool is_running = true;
static Uint32 last_frame_time = 0;
static float delta_time = 0.0f;

bool engine_init(const char* title, int width, int height)
{
    if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) != 0)
    {
        printf("Engine init error: %s\n", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow(title,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_SHOWN);

    if (!window)
    {
        printf("Window creation error: %s\n", SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!renderer_init(renderer))
    {
        printf("Renderer creation error: %s\n", SDL_GetError());
        return false;
    }

    ecs_init();

    last_frame_time = SDL_GetTicks();
    return true;
}

void engine_handle_input()
{
    input_update();
    if (input_should_quit())
    {
        is_running = false;
    }
}

bool engine_running()
{
    return is_running;
}

float engine_delta_time()
{
    return delta_time;
}

SDL_Renderer* engine_renderer()
{
    return renderer;
}

void engine_begin_frame()
{
    Uint32 current_time = SDL_GetTicks();
    delta_time = (float)(current_time - last_frame_time) / 1000.0f;
    last_frame_time = current_time;

    SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
    SDL_RenderClear(renderer);
}

void engine_end_frame()
{
    SDL_RenderPresent(renderer);
}

void engine_shutdown()
{
    if (window) SDL_DestroyWindow(window);
    if (renderer) renderer_shutdown();
    SDL_Quit();
}
