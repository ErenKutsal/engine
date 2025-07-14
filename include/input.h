//
// Created by Ahmet Eren Kutsal on 9.07.2025.
//

#ifndef INPUT_H
#define INPUT_H
#include <SDL_scancode.h>
#include <stdbool.h>

void input_update();
bool input_is_down(SDL_Scancode sc);
bool input_should_quit();

#endif //INPUT_H
