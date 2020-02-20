#ifndef POSITION_H
#define POSITION_H

#include "segment.h"

struct Position
{
    Position();
    Position(float x, float y, float theta, float velocity);
    void move_to(float x, float y, float theta, float velocity);
    float x;
    float y;
    float theta;
    float theta_degree;
    float velocity;
    Vec2f pos_vec2f;
};

#endif