//
// Created by Ahmet Eren Kutsal on 9.07.2025.
//

#include "../engine/engine.h"
#include "../engine/renderer.h"
#include "../engine/ecs/entity.h"
#include "../engine/ecs/components/component_transform.h"
#include "../engine/ecs/components/component_sprite.h"
#include "../engine/ecs/systems/system_movement.h"
#include "../engine/ecs/systems/system_render.h"

#include <stdio.h>

#include "../engine/ecs/components/component_collider.h"
#include "../engine/ecs/components/component_tag.h"

int main(void)
{
    if (!engine_init("Renderer Test", 800, 600)) return 1;

    Texture* tex = renderer_load_texture("assets/player.png");
    if (!tex) {
        fprintf(stderr, "Failed to load player texture!\n");
        engine_shutdown();
        return 1;
    }

    EntityID player = entity_create();
    transform_set(player, 100, 100, 0, 0, 10);
    collider_set(player, 0, 0, 64, 64, false);
    input_enable(player);
    tag_set(player, TAG_PLAYER);
    sprite_add_layer(player, tex, 0, 0, true);

    EntityID enemy = entity_create();
    transform_set(enemy, 500, 100, 0, 0, 100);
    collider_set(enemy, 0, 0, 64, 64, false);
    tag_set(enemy, TAG_ENEMY);
    sprite_add_layer(enemy, tex, 0, 0, true);


    while (engine_running())
    {
        engine_handle_input();
        engine_begin_frame();

        /*
        if (tex)
        {
            renderer_draw_texture(tex, 100, 100);
        }
        */
        movement_update(engine_delta_time());
        system_render_draw_all();

        //printf("Delta: %f\n", engine_delta_time());
        SDL_Delay(16); // crude ~60fps cap (1000ms / 60 = ~16.6ms)

        engine_end_frame();
    }

    renderer_free_texture(tex);
    engine_shutdown();
    return 0;
}
