//
// Created by Ahmet Eren Kutsal on 9.07.2025.
//

#include "../engine/engine.h"
#include "../engine/renderer.h"
#include "../engine/ecs/entity.h"
#include "../engine/ecs/component_transform.h"
#include "../engine/ecs/component_sprite.h"
#include "../engine/ecs/system_movement.h"
#include "../engine/ecs/system_render.h"

#include <stdio.h>

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
    transform_set(player, 100, 100, 100, 100);
    sprite_add_layer(player, tex, 0, 0, true);

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

        printf("Delta: %f\n", engine_delta_time());
        SDL_Delay(16); // crude ~60fps cap (1000ms / 60 = ~16.6ms)

        engine_end_frame();
    }

    renderer_free_texture(tex);
    engine_shutdown();
    return 0;
}