#include "position.h"
#include "segment.h"


Position::Position()
{
    x = 0;
    y = 0;
    theta = 0;
    position_vector = Vec2f(x, y);
}

Position::Position(float x, float y, float theta)
// Position::Position(float x, float y, float theta, float velocity)
{
    this->x = x;
    this->y = y;
    this->theta_degree = theta;
    this->theta = theta * (M_PI / 180.0);
    position_vector = Vec2f(x, y);
}

void Position::move_to(float x, float y, float theta)
{
    this->x = x;
    this->y = y;
    this->theta = theta;
    position_vector = Vec2f(x, y);
}