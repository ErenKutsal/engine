//
// Created by Ahmet Eren Kutsal on 14.07.2025.
//

#include "../include/my_math.h"

bool near_zero(float value)
{
    return (value < EPSILON) && (value > -EPSILON);
}

bool vec2f_near_zero(Vec2f v)
{
    return near_zero(v.x) && near_zero(v.y);
}

Vec2f vec2f_add(const Vec2f a, const Vec2f b)
{
    return (Vec2f) {a.x + b.x, a.y + b.y};
}

Vec2f vec2f_sub(const Vec2f a, const Vec2f b)
{
    return (Vec2f) {a.x - b.x, a.y - b.y};
}

Vec2f vec2f_mul(const Vec2f a, float scalar)
{
    return (Vec2f) {a.x * scalar, a.y * scalar};
}

Vec2f vec2f_div(const Vec2f a, float scalar)
{
    if (!scalar) return VEC2F_ZERO;
    return (Vec2f) {a.x / scalar, a.y / scalar};
}

Vec2f vec2f_normalize(const Vec2f v)
{
    float length = SQRTF((v.x * v.x) + (v.y * v.y));
    if (!length) return v;
    return (Vec2f) {v.x / length, v.y / length};
}

float vec2f_dot(const Vec2f a, const Vec2f b)
{
    return (a.x * b.x) + (a.y * b.y);
}

float vec2f_length(const Vec2f v)
{
    return SQRTF((v.x * v.x) + (v.y * v.y));
}

float vec2f_distance(const Vec2f a, const Vec2f b)
{
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}