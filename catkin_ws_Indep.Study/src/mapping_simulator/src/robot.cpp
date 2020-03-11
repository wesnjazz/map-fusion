#include "robot.h"
#include "simulator.h"
#include "transformation.h"


Robot::Robot()
{
    ;
}

Robot::Robot(Vec2f &position, float heading_degree, float speed)
{
    this->position_W = position;
    this->heading_degree = heading_degree;
    this->heading_radian = heading_degree * (M_PI / 180.0);
    this->speed = speed;
    this->set_velocity();
}


void Robot::move_to(Vec2f &position)
{
    this->heading_degree = get_angle_degree_between_two_vectors(this->position_W, position);
    this->heading_radian = degree_to_radian(heading_degree);
    this->position_W = position;
    this->set_velocity();
    cout << "robot angle:" << heading_degree << "\t"<< heading_radian << endl;
}


void Robot::set_speed(float speed)
{
    this->speed = speed;
    this->set_velocity();
}


void Robot::set_heading(float heading_degree)
{
    this->heading_degree = heading_degree;
    this->heading_radian = degree_to_radian(heading_degree);
    this->set_velocity();
}


void Robot::set_velocity()
{
    /** Todo: 
     * - Make a helper function of creating a vector(speed, angle). 
     * - Robot's velocity_W = robot.position + robot's velocity_R
     **/
    float x = this->position_W.x() + (this->speed * cos(heading_radian));
    float y = this->position_W.y() + (this->speed * sin(heading_radian));
    this->velocity = Vec2f(x, y);
}