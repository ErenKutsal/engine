//
// Created by Ahmet Eren Kutsal on 12.07.2025.
//

#include "ecs_init.h"
#include "component_transform.h"
#include "component_sprite.h"
#include "entity.h"

void ecs_init()
{
    entity_system_init();
    transform_init();
    sprite_init();
}
void ecs_shutdown()
{

}