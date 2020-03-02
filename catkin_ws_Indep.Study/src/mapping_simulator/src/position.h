#ifndef POSITION_H
#define POSITION_H

#include <vector>
#include "segment.h"


struct Position
{
    Position();
    Position(float x, float y);
    Position(float x, float y, float theta);
    void new_position(float x, float y);
    void new_position(float x, float y, float theta);
    void update_position_vector();
    vector<Position> calculate_curve_points(Position &p1, int addiotional_num_cut = 0, int default_num_cut = 10);
    float x;
    float y;
    float theta_radian;
    float theta_degree;
    Vec2f position_vector;
    vector<Position> curves;

    Position operator*(float const k)
    {
        Position p;
        p.x = this->x * k;
        p.y = this->y * k;
        p.theta_radian = this->theta_radian;
        p.theta_degree = this->theta_degree;
        p.update_position_vector();
        return p;
    }

    friend std::ostream& operator<<(std::ostream& os, const Position &pos)
    {
        float x = pos.x;
        float y = pos.y;
        os << "(" << to_string(pos.x) << "," << to_string(pos.y) << "," << to_string(pos.theta_degree) << ")";
        return os;
    }

};

#endif