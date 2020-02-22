#ifndef POSITION_H
#define POSITION_H

#include "segment.h"

struct Position
{
    Position();
    Position(float x, float y, float theta);
    void move_to(float x, float y, float theta);
    float x;
    float y;
    float theta;
    float theta_degree;
    Vec2f position_vector;
};

#endif