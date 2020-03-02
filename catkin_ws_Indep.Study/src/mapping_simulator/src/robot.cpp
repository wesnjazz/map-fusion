#include "robot.h"


Robot::Robot(Position position, double speed)
{
    this->position = position;
    this->speed = speed;
    this->set_velocity();
}

void Robot::move_to(Position position)
{
    this->position = position;
    this->set_velocity();
}

void Robot::set_speed(double speed)
{
    this->speed = speed;
    this->set_velocity();
}

void Robot::set_velocity()
{
    double x = this->speed * cos(this->position.theta_radian);
    double y = this->speed * sin(this->position.theta_radian);
    this->velocity = Vec2f(x, y);
}