//
// Created by Ahmet Eren Kutsal on 9.07.2025.
//

#include "../include/engine.h"
#include "../include/renderer.h"
#include "../include/ecs/entity.h"
#include "../include/ecs/components/component_transform.h"
#include "../include/ecs/components/component_sprite.h"
#include "../include/ecs/systems/system_movement.h"
#include "../include/ecs/systems/system_render.h"

#include <stdio.h>

#include "../include/key_binding.h"
#include "../include/ecs/components/component_collider.h"
#include "../include/ecs/components/component_tag.h"
#include "../include/camera.h"
#include "../include/map/map_parser.h"

#include "player.h"

#define FRAME_TARGET_TIME 16

int main(void)
{
    if (!engine_init("Renderer Test", 800, 600)) return 1;

    Texture* tex = renderer_load_texture("assets/player.png");
    if (!tex) {
        fprintf(stderr, "Failed to load player texture!\n");
        engine_shutdown();
        return 1;
    }
    tex->width = 32;
    tex->height = 32;
    EntityID player = entity_create();
    transform_set(player, 100, 100, 0, 0, 100.0f, 100.0f);
    collider_set(player, 0, 0, 32, 32, false);
    input_enable(player);
    tag_set(player, TAG_PLAYER);
    sprite_add_layer(player, tex, 0, 0, true);

    EntityID enemy = entity_create();
    transform_set(enemy, 500, 100, 0, 0, 100.0f, 100.0f);
    collider_set(enemy, 0, 0, 32, 32, false);
    tag_set(enemy, TAG_ENEMY);
    sprite_add_layer(enemy, tex, 0, 0, true);

    bind_key(SDL_SCANCODE_SPACE, player_attack, "attack", player);

    camera_init(800, 600);
    camera_set_target(player);

    Map* map = parse_map("assets/maps/map1.map");
    map_set(map);

    Uint32 frame_start;
    int frame_time;

    while (engine_running())
    {
        frame_start = SDL_GetTicks();

        engine_handle_input();
        engine_begin_frame();

        /*
        if (tex)
        {
            renderer_draw_texture(tex, 100, 100);
        }
        */
        movement_update(engine_delta_time());
        camera_update(engine_delta_time());
        system_render_draw_all(map);

        frame_time = SDL_GetTicks() - frame_start;
        if (FRAME_TARGET_TIME > frame_time)
        {
            SDL_Delay(FRAME_TARGET_TIME - frame_time);
        }
        //printf("Delta: %f\n", engine_delta_time());
        SDL_Delay(16); // crude ~60fps cap (1000ms / 60 = ~16.6ms)

        engine_end_frame();
    }

    renderer_free_texture(tex);
    engine_shutdown();
    return 0;
}
