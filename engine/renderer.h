//
// Created by Ahmet Eren Kutsal on 9.07.2025.
//

#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <stdbool.h>

typedef struct
{
    SDL_Texture* texture;
    int width;
    int height;
} Texture;

bool renderer_init(SDL_Renderer* sdl_renderer);
Texture* renderer_load_texture(const char* file);
void renderer_draw_texture(Texture* texture, int x, int y);
void renderer_free_texture(Texture* texture);
void renderer_shutdown();

#endif //RENDERER_H
