#ifndef ROBOT_H
#define ROBOT_H

// #include <vector>
// #include "trajectory.h"
#include "laser.h"
#include "position.h"
// #include "laser_parameter.h"

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