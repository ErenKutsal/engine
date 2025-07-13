//
// Created by Ahmet Eren Kutsal on 9.07.2025.
//

#ifndef ENGINE_H
#define ENGINE_H

#include <stdbool.h>
#include <SDL2/SDL.h>

bool engine_init(const char* title, int width, int height);
void engine_handle_input();
bool engine_running();
float engine_delta_time();
void engine_begin_frame();
void engine_end_frame();
void engine_shutdown();
SDL_Renderer* engine_renderer();

#endif //ENGINE_H
