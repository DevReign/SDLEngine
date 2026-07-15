#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct {
    float x;
    float y;
} Vec2;

Vec2 Vec2Create(int x, int y);

// Standard algebraic operations
Vec2  Vec2Add(Vec2 a, Vec2 b);
Vec2  Vec2Sub(Vec2 a, Vec2 b);
Vec2  Vec2Scale(Vec2 v, float scalar);

// Length and direction checking utilities
float Vec2Length(Vec2 v);
Vec2  Vec2Normalize(Vec2 v);
float Vec2Distance(Vec2 a, Vec2 b);

#endif