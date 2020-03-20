#ifndef ROBOT_H
#define ROBOT_H

#include "laser.h"
#include "position.h"

struct Robot
{
    Robot();
    Robot(Position pos);
    float velocity;
    Position position;
    Laser sensor_laser;
    // WheelEncoder sensor_wheel_encoder;

};

#endif