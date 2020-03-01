#include "robot.h"


Robot::Robot(Position pos)
{
    position = pos;
}

void Robot::move_to(Position pos)
{
    position = pos;
}