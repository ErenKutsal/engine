//
// Created by Ahmet Eren Kutsal on 12.07.2025.
//

#include "../../../include/ecs/components/component_sprite.h"
#include "../../../include/ecs/components/component_transform.h"
#include "../../../include/ecs/entity.h"
#include "../../../include/engine.h"
#include "../../../include/renderer.h"
#include "../../../include/ecs/components/component_collider.h"
#include "../../../include/ecs/systems/system_render.h"

void system_render_draw_all(Map* map)
{
    Camera cam = camera_get();
    SDL_Renderer* renderer = engine_renderer();
    system_render_draw_map(map, cam, renderer);

    for (int i = 0; i < MAX_ENTITIES; i++)
    {
        EntityID id = {i, entity_get_generation(i)};
        if (!entity_is_alive(id)) continue;

        Transform* t = transform_get(id);
        int x = (int) (t->pos_x - cam.x) ? : 0;
        int y = (int) (t->pos_y - cam.y) ? : 0;
        //int dx = (int) t->dx ? : 0;
        //int dy = (int) t->dy ? : 0;

        Sprite* s = sprite_get(id);
        for (int j = 0; j < s->count; j++)
        {
            SpriteLayer l = s->layers[j];
            if (!l.visible) continue;

            renderer_draw_texture(l.tex, x + l.offset_x, y + l.offset_y);
        }
        Collider* c = collider_get(id);

        SDL_Rect rect = {x + c->offset_x, y + c->offset_y, c->width, c->height};

        // Set draw color (e.g., green)
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

        // Draw rectangle outline for debug
        SDL_RenderDrawRect(renderer, &rect);
    }
}

void system_render_draw_map(Map* map, Camera cam, SDL_Renderer* renderer)
{
    Texture* tex = map->tileset->texture;
    for (int y = 0; y < map->map_height; y++) {
        for (int x = 0; x < map->map_width; x++) {
            int tile_index = map->map_data[y * map->map_width + x];
            int tile_width = map->tile_width;
            int tile_height = map->tile_height;
            SDL_Rect src_rect = (SDL_Rect) {
                .x = (tile_index % map->tileset->cols) * tile_width,
                .y = (tile_index / map->tileset->cols) * tile_height,
                .w = tile_width,
                .h = tile_height};
            SDL_Rect dest_rect = {
                x * tile_width - cam.x,
                y * tile_height - cam.y,
                tile_width,
                tile_height};
            SDL_SetTextureAlphaMod(tex->texture, 128); // 50% transparent
            SDL_RenderCopy(renderer, tex->texture, &src_rect, &dest_rect);
        }
    }
}
