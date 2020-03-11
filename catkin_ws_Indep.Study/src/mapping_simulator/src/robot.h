#ifndef ROBOT_H
#define ROBOT_H

#include "laser.h"


struct Robot
{
    Robot();
    Robot(Vec2f &position_W, float heading_degree = 0.0, float speed = 0.2);
    void move_to(Vec2f &position_W);
    void set_speed(float speed);
    void set_heading(float heading);
    void set_velocity();

    Vec2f position_W;                 // Position in world frame
    Vec2f velocity;                 // Speed and Direction
    float heading_degree;
    float heading_radian;
    float speed;
    Laser sensor_laser;
    // WheelEncoder sensor_wheel_encoder;
};

#endif