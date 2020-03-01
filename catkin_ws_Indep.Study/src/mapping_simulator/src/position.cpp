#include "position.h"


Position::Position()
{
    x = 0;
    y = 0;
    theta_radian = 0;
    theta_degree = 0;
    position_vector = Vec2f(x, y);
}

Position::Position(float x, float y)
{
    this->x = x;
    this->y = y;
    this->theta_degree = 0;
    this->theta_radian = theta_radian * (M_PI / 180.0);
    position_vector = Vec2f(x, y);
}

Position::Position(float x, float y, float theta)
{
    this->x = x;
    this->y = y;
    this->theta_degree = theta;
    this->theta_radian = theta_radian * (M_PI / 180.0);
    position_vector = Vec2f(x, y);
}

void Position::new_position(float x, float y)
{
    this->x = x;
    this->y = y;
    position_vector = Vec2f(x, y);
}

void Position::new_position(float x, float y, float theta)
{
    this->x = x;
    this->y = y;
    this->theta_degree = theta;
    this->theta_radian = theta_radian * (M_PI / 180.0);
    position_vector = Vec2f(x, y);
}