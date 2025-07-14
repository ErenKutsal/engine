//
// Created by Ahmet Eren Kutsal on 14.07.2025.
//

#ifndef MATH_H
#define MATH_H

#include <math.h>
#include <stdbool.h>

#define SQRTF sqrtf

#define EPSILON 0.0001f

#define VEC2F_ZERO vec2f(0,0)

typedef struct
{
    float x, y;
} Vec2f;

static inline Vec2f vec2f (float x, float y)
{
    return (Vec2f) {x, y};
}

bool near_zero(float value);

//immutable operations on vectors
bool vec2f_near_zero(Vec2f v);
Vec2f vec2f_add(const Vec2f a, const Vec2f b);
Vec2f vec2f_sub(const Vec2f a, const Vec2f b);
Vec2f vec2f_mul(const Vec2f a, float scalar);
Vec2f vec2f_div(const Vec2f a, float scalar);
Vec2f vec2f_normalize(const Vec2f v);
float vec2f_dot(const Vec2f a, const Vec2f b);
float vec2f_length(const Vec2f v);
float vec2f_distance(const Vec2f a, const Vec2f b);


#endif //MATH_H
