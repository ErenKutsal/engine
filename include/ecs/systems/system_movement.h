//
// Created by Ahmet Eren Kutsal on 12.07.2025.
//

#ifndef SYSTEM_MOVEMENT_H
#define SYSTEM_MOVEMENT_H

#include "../entity.h"
#include "../components/component_input.h"
#include "../../../include/my_math.h"

void movement_update(float delta_time);

static Vec2f player_request_update(EntityID player, Input* input);
static Vec2f projectile_request_update(EntityID projectile);
static Vec2f predict_update(EntityID id);

#endif //SYSTEM_MOVEMENT_H
