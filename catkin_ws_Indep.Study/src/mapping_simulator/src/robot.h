#ifndef ROBOT_H
#define ROBOT_H

#include "position.h"
#include "laser.h"


struct Robot
{
    Robot();
    Robot(Position pos, double speed = 0.2);
    void move_to(Position pos);
    void set_speed(double speed);
    void set_velocity();

    double speed;
    Vec2f velocity;                 // Speed and Direction
    Position position;              // Position in world frame
    Laser sensor_laser;
    // WheelEncoder sensor_wheel_encoder;

};

#endif