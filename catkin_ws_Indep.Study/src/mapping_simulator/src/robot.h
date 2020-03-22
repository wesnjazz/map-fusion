#ifndef ROBOT_H
#define ROBOT_H

#include "laser.h"


struct Robot
{
    Robot();
    Robot(Vec2f &position_in_Wframe, float heading_degree = 0.0, float speed = 0.2);
    void move_to(Vec2f &position_in_Wframe);
    void set_speed(float speed);
    void set_heading(float heading);
    void set_velocity();
    void set_robot_frame();

    Vec2f position_in_Wframe;                 // Position in world frame
    Vec2f velocity_in_Wframe;                 // Speed and Direction
    Vec3f robot_frame_in_Wframe;
    float heading_degree_in_Wframe;
    float heading_radian_in_Wframe;
    float speed;
    Laser sensor_laser;
    const float outer_radius = 1;
    // WheelEncoder sensor_wheel_encoder;
};

#endif