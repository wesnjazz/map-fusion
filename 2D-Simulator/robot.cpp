#include "robot.h"
#include "laser.h"

Robot::Robot(Position pos)
{
    position = pos;
}

void Robot::laser_scan(Position pos)
{
    Laser laser = Laser(pos);
    laser.create_rays();
    // laser.print_rays();
}
