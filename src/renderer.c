//
// Created by Ahmet Eren Kutsal on 9.07.2025.
//

#include "../include/renderer.h"

#include <SDL2/SDL_image.h>

static SDL_Renderer* renderer = NULL;

bool renderer_init(SDL_Renderer* sdl_renderer)
{
    renderer = sdl_renderer;

    const int flags = IMG_INIT_PNG;
    if (!(IMG_Init(flags) & flags))
    {
        printf("SDL_image init error: %s\n", IMG_GetError());
        return false;
    }

    return true;
}

Texture* renderer_load_texture(const char* file)
{
    SDL_Surface* surface = IMG_Load(file);
    if (!surface)
    {
        printf("IMG_Load failed");
        return NULL;
    }

    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surface);
    if (!tex)
    {
        printf("SDL_CreateTextureFromSurface failed.");
        return NULL;
    }

    Texture* t = malloc(sizeof(Texture));

    t->texture = tex;
    t->height = surface->h;
    t->width = surface->w;

    SDL_FreeSurface(surface);
    return t;
}

void renderer_draw_texture(Texture* tex, int x, int y)
{
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    dst.w = tex->width;
    dst.h = tex->height;
    SDL_RenderCopy(renderer, tex->texture, NULL, &dst);
}

void renderer_free_texture(Texture* tex)
{
    if (tex)
    {
        SDL_DestroyTexture(tex->texture);
        free(tex);
    }
}

void renderer_shutdown()
{
    IMG_Quit();
}
