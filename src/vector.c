#include "vector.h"

Vec2 Vec2Add(Vec2 a, Vec2 b) {
    Vec2 result = { a.x + b.x, a.y + b.y };
    return result;
}

Vec2 Vec2Sub(Vec2 a, Vec2 b) {
    Vec2 result = { a.x - b.x, a.y - b.y };
    return result;
}

Vec2 Vec2Scale(Vec2 v, float scalar) {
    Vec2 result = { v.x * scalar, v.y * scalar };
    return result;
}

float Vec2Length(Vec2 v) {
    return sqrtf(v.x * v.x + v.y * v.y);
}

Vec2 Vec2Normalize(Vec2 v) {
    float len = Vec2Length(v);
    if (len > 0.0f) {
        Vec2 result = { v.x / len, v.y / len };
        return result;
    }
    Vec2 zero = { 0.0f, 0.0f };
    return zero;
}

float Vec2Distance(Vec2 a, Vec2 b) {
    return Vec2Length(Vec2Sub(a, b));
}
