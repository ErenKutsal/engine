//
// Created by Ahmet Eren Kutsal on 12.07.2025.
//

#include "../../include/ecs/ecs_init.h"
#include "../../include/ecs/components/component_transform.h"
#include "../../include/ecs/components/component_sprite.h"
#include "../../include/ecs/components/component_input.h"
#include "../../include/ecs/components/component_collider.h"
#include "../../include/ecs/components/component_tag.h"
#include "../../include/ecs/components/component_script.h"
#include "../../include/ecs/entity.h"

void ecs_init()
{
    entity_system_init();
    transform_init();
    sprite_init();
    input_init();
    collider_init();
    tag_init();
    script_init();
}
void ecs_shutdown()
{

}