#include "robot.h"
#include "simulator.h"
#include "transformation.h"

Robot::Robot(Vec2f &position, float angle_degree, float speed)
{
    this->position = position;
    this->angle_degree = angle_degree;
    this->angle_radian = angle_degree * (M_PI / 180.0);
    this->speed = speed;
    this->set_velocity();
}


void Robot::move_to(Vec2f &position)
{
    this->angle_degree = get_angle_degree_between_two_vectors(this->position, position);
    this->angle_radian = degree_to_radian(angle_degree);
    this->position = position;
    this->set_velocity();
    cout << "robot angle:" << angle_degree << "\t"<< angle_radian << endl;
}


void Robot::set_speed(float speed)
{
    this->speed = speed;
    this->set_velocity();
}


void Robot::set_velocity()
{
    float x = this->position.x() + (this->speed * cos(angle_radian));
    float y = this->position.y() + (this->speed * sin(angle_radian));
    this->velocity = Vec2f(x, y);
}