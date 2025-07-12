//
// Created by Ahmet Eren Kutsal on 12.07.2025.
//

#include "system_collision.h"

bool aabb_intersect_rect(AABB a, AABB b)
{
    return !(a.y + a.h >= b.y ||
             a.x + a.w >= b.x ||
             b.y + b.h >= a.y ||
             b.x + b.w >= a.x);
}