#include "robot.h"
#include "simulator.h"
#include "transformation.h"


Robot::Robot()
{
    this->position_in_Wframe = Vec2f(0, 0);
    this->heading_degree_in_Wframe = 0;
    this->heading_radian_in_Wframe = 0;
    this->speed = 0.2;
    this->set_velocity();
    this->set_robot_frame();
}

Robot::Robot(Vec2f &position, float heading_degree_in_Wframe, float speed)
{
    this->position_in_Wframe = position;
    // cout << "position_in_Wframe:\n" << this->position_in_Wframe << endl
        // << "position:\n" << position << endl;
    this->heading_degree_in_Wframe = heading_degree_in_Wframe;
    this->heading_radian_in_Wframe = heading_degree_in_Wframe * (M_PI / 180.0);
    this->speed = speed;
    this->set_velocity();
    this->set_robot_frame();
}


void Robot::move_to(Vec2f &position)
{
    this->heading_degree_in_Wframe = get_angle_degree_between_two_vectors(this->position_in_Wframe, position);
    this->heading_radian_in_Wframe = degree_to_radian(heading_degree_in_Wframe);
    this->position_in_Wframe = position;
    this->set_velocity();
    this->set_robot_frame();
    // cout << "robot angle:" << heading_degree_in_Wframe << "\t"<< heading_radian_in_Wframe << endl;
}


void Robot::set_speed(float speed)
{
    this->speed = speed;
    this->set_velocity();
}


void Robot::set_heading(float heading_degree_in_Wframe)
{
    this->heading_degree_in_Wframe = heading_degree_in_Wframe;
    this->heading_radian_in_Wframe = degree_to_radian(heading_degree_in_Wframe);
    this->set_velocity();
    this->set_robot_frame();
}


void Robot::set_velocity()
{
    /** Todo: 
     * - Make a helper function of creating a vector(speed, angle). 
     * - Robot's velocity_W = robot.position + robot's velocity_R
     **/
    float x = this->position_in_Wframe.x() + (this->speed * cos(heading_radian_in_Wframe));
    float y = this->position_in_Wframe.y() + (this->speed * sin(heading_radian_in_Wframe));
    this->velocity_in_Wframe = Vec2f(x, y);
}


void Robot::set_robot_frame()
{
    this->robot_frame_in_Wframe = Vec3f(this->position_in_Wframe.x(), this->position_in_Wframe.y(), this->heading_degree_in_Wframe);
}