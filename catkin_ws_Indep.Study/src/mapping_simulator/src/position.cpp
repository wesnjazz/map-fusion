#include "position.h"
#include "segment.h"

Position::Position()
{
    x = 0;
    y = 0;
    theta_radian = 0;
    theta_degree = 0;
    position_vector = Vec2f(x, y);
}

Position::Position(float x, float y)
{
    this->x = x;
    this->y = y;
    this->theta_degree = 0;
    this->theta_radian = theta_radian * (M_PI / 180.0);
    position_vector = Vec2f(x, y);
}

Position::Position(float x, float y, float theta)
{
    this->x = x;
    this->y = y;
    this->theta_degree = theta;
    this->theta_radian = theta_radian * (M_PI / 180.0);
    position_vector = Vec2f(x, y);
}

void Position::new_position(float x, float y)
{
    this->x = x;
    this->y = y;
    position_vector = Vec2f(x, y);
}

void Position::new_position(float x, float y, float theta)
{
    this->x = x;
    this->y = y;
    this->theta_degree = theta;
    this->theta_radian = theta_radian * (M_PI / 180.0);
    position_vector = Vec2f(x, y);
}


void Position::update_position_vector()
{
    this->position_vector = Vec2f(this->x, this->y);
}


vector<Position> Position::calculate_curve_points(Position &p1, int addiotional_num_cut, int default_num_cut)
{
    Vec2f L0 = this->position_vector;
    Vec2f L1 = p1.position_vector - L0;

    // Segment s = Segment()

    vector<Position> curves;

    return curves;
}
