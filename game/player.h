//
// Created by Ahmet Eren Kutsal on 14.07.2025.
//

#ifndef PLAYER_H
#define PLAYER_H

#include "../include/ecs/entity.h"
#include "../include/ecs/systems/system_collision.h"

EntityID player_create();
void player_attack(EntityID player);
void on_collision(EntityID self, EntityID other, CollisionDirection direction);

#endif //PLAYER_H
