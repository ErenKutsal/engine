//
// Created by Ahmet Eren Kutsal on 12.07.2025.
//

#include "../components/component_sprite.h"
#include "../components/component_transform.h"
#include "../entity.h"
#include "../../engine.h"
#include "../../renderer.h"
#include "../components/component_collider.h"

void system_render_draw_all()
{
    for (int i = 0; i < MAX_ENTITIES; i++)
    {
        EntityID id = {i, entity_get_generation(i)};
        if (!entity_is_alive(id)) continue;

        Transform* t = transform_get(id);
        int x = (int) t->pos_x ? : 0;
        int y = (int) t->pos_y ? : 0;
        int dx = (int) t->dx ? : 0;
        int dy = (int) t->dy ? : 0;

        Sprite* s = sprite_get(id);
        for (int j = 0; j < s->count; j++)
        {
            SpriteLayer l = s->layers[j];
            if (!l.visible) continue;

            renderer_draw_texture(l.tex, x + l.offset_x, y + l.offset_y);
        }
        Collider* c = collider_get(id);

        SDL_Rect rect = {x + c->offset_x, y + c->offset_y, c->width, c->height};
        SDL_Renderer* renderer = engine_renderer();
        // Set draw color (e.g., green)
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

        // Draw rectangle outline
        SDL_RenderDrawRect(renderer, &rect);
    }
}
