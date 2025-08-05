//
// Created by Ahmet Eren Kutsal on 16.07.2025.
//

#include "../../include/map/map_loader.h"
#include "../../include/ecs/entity.h"
#include "../../include/ecs/components/component_transform.h"
#include "../../include/ecs/components/component_collider.h"
#include "../../include/ecs/components/component_tag.h"
#include "../../include/ecs/components/component_sprite.h"

int load_map(Map* map)
{
    if (strlen(map->tileset->filename) == 0)
    {
        return 1;
    }

    map->tileset->texture = renderer_load_texture(map->tileset->filename);
    for (int i = 0; i < map->entity_data_count; i++)
    {
        EntityData data = map->entity_datas[i];
        EntityID entity = entity_create();
        transform_set(entity,
            (float) (data.x * map->tile_width),
            (float) (data.y * map->tile_height),
            0, 0,
            0, 0);
        printf("%f\n", (float) (data.x));
        printf("%f\n", (float) (data.y));
        //temporary
        Texture* tex = renderer_load_texture("assets/player.png");
        if (!tex) {
            fprintf(stderr, "Failed to load entity texture!\n");
            return 1;
        }
        tex->width = 32;
        tex->height = 32;
        //temporary
        collider_set(entity, 0, 0, 32, 32, false);
        tag_set(entity, TAG_ENEMY);
        sprite_add_layer(entity, tex, 0, 0, true);
    }
    return 0;
}

//map_free does the job for now.
void unload_map(Map* map)
{

}