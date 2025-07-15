//
// Created by Ahmet Eren Kutsal on 15.07.2025.
//

#include "../include/camera.h"

#include "../include/ecs/components/component_transform.h"

static Camera cam;

void camera_init(float width, float height)
{
    cam.x = 0;
    cam.y = 0;
    cam.width = width;
    cam. height = height;
    cam.target = ENTITY_NONE;
}

void camera_set_target(EntityID target)
{
    if (target.index >= MAX_ENTITIES) return;
    cam.target = target;
}

void camera_update(float delta_time)
{
    if (!entity_is_alive(cam.target) || !transform_has(cam.target)) return;

    const Transform* target_transform = transform_get(cam.target);
    cam.x = target_transform->pos_x - cam.width / 2;
    cam.y = target_transform->pos_y - cam.height / 2;
}

Camera camera_get()
{
    return cam;
}