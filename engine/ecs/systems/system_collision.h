//
// Created by Ahmet Eren Kutsal on 12.07.2025.
//

#ifndef SYSTEM_COLLISION_H
#define SYSTEM_COLLISION_H
#include <stdbool.h>

typedef struct
{
    float x, y, w, h;
} AABB;

bool aabb_intersect_rect(AABB a, AABB b);

#endif //SYSTEM_COLLISION_H
