//
// Created by Ahmet Eren Kutsal on 12.07.2025.
//

#ifndef SYSTEM_MOVEMENT_H
#define SYSTEM_MOVEMENT_H

#include "../entity.h"
#include "../components/component_input.h"

void movement_update(float delta_time);
void player_request_update(EntityID player, Input* input);
void predict_update(EntityID id);

#endif //SYSTEM_MOVEMENT_H
