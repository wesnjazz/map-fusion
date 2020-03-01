#ifndef ROBOT_H
#define ROBOT_H

#include "position.h"
#include "laser.h"


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