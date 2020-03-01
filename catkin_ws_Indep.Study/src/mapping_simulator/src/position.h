#ifndef POSITION_H
#define POSITION_H

#include "segment.h"


struct Position
{
    Position();
    Position(float x, float y);
    Position(float x, float y, float theta);
    void new_position(float x, float y);
    void new_position(float x, float y, float theta);
    float x;
    float y;
    float theta_radian;
    float theta_degree;
    Vec2f position_vector;

    friend std::ostream& operator<<(std::ostream& os, const Position &pos)
    {
        float x = pos.x;
        float y = pos.y;
        os << "(" << to_string(pos.x) << "," << to_string(pos.y) << "," << to_string(pos.theta_degree) << ")";
        return os;
    }

};

#endif