#include "position.h"
#include "segment.h"


Position::Position()
{
    x = 0;
    y = 0;
    theta = 0;
    velocity = 0;
    pos_vec2f = Vec2f(x, y);
}

Position::Position(float x, float y, float theta, float velocity)
{
    this->x = x;
    this->y = y;
    this->theta_degree = theta;
    this->theta = theta * (M_PI / 180.0);
    this->velocity = velocity;
    pos_vec2f = Vec2f(x, y);
}

void Position::move_to(float x, float y, float theta, float velocity)
{
    this->x = x;
    this->y = y;
    this->theta = theta;
    this->velocity = velocity;
    pos_vec2f = Vec2f(x, y);
}