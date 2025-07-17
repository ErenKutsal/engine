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
    for (int y = 0; y < map->height; y++) {
        for (int x = 0; x < map->width; x++) {
            Tile tile = map->tiles[y * map->width + x];
            SDL_Rect src_rect = (SDL_Rect) {
                .x = (tile.index % map->tileset->cols) * tile.size,
                .y = (tile.index / map->tileset->cols) * tile.size,
                .w = map->tileset->tile_size,
                .h = map->tileset->tile_size};
            SDL_Rect dest_rect = {
                x * map->tileset->tile_size - cam.x,
                y * map->tileset->tile_size - cam.y,
                map->tileset->tile_size,
                map->tileset->tile_size};
            SDL_RenderCopy(renderer, tex->texture, &src_rect, &dest_rect);
        }
    }
}
