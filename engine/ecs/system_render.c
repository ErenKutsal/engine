//
// Created by Ahmet Eren Kutsal on 12.07.2025.
//

#include "component_sprite.h"
#include "component_transform.h"
#include "entity.h"
#include "../renderer.h"

void system_render_draw_all()
{
    for (int i = 0; i < MAX_ENTITIES; i++)
    {
        EntityID id = {i, entity_get_generation(i)};
        if (!entity_is_alive(id)) continue;

        Transform* t = transform_get(id);
        int x = (int) t->pos_x ? : 0;
        int y = (int) t->pos_y ? : 0;

        Sprite* s = sprite_get(id);
        for (int j = 0; j < s->count; j++)
        {
            SpriteLayer l = s->layers[j];
            if (!l.visible) continue;

            renderer_draw_texture(l.tex, x + l.offset_x, y + l.offset_y);
        }
    }
}
