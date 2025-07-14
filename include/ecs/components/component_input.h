//
// Created by Ahmet Eren Kutsal on 12.07.2025.
//

#ifndef COMPONENT_INPUT_H
#define COMPONENT_INPUT_H

#include "../entity.h"

#include <stdbool.h>

typedef struct {
    bool move_up;
    bool move_down;
    bool move_left;
    bool move_right;
    bool attack;
    bool shoot;
} Input;

void input_init();
void input_enable(EntityID id);
void input_set(EntityID id, Input input);
Input* input_get(EntityID id);
void input_clear(EntityID id);
bool input_has(EntityID id);

#endif //COMPONENT_INPUT_H
