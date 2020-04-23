#ifndef POSITION_H
#define POSITION_H

#include <vector>
#include "segment.h"


struct Position
{
    Position();
    Position(double x, double y);
    Position(double x, double y, double theta);
    void new_position(double x, double y);
    void new_position(double x, double y, double theta);
    void update_position_vector();
    double x;
    double y;
    double theta_radian;
    double theta_degree;
    Vec2f position_vector;
    vector<Position> curves;

    Position operator*(double const k)
    {
        Position p;
        p.x = this->x * k;
        p.y = this->y * k;
        p.theta_radian = this->theta_radian;
        p.theta_degree = this->theta_degree;
        p.update_position_vector();
        return p;
    }

    Position operator+(const Position &k)
    {
        Position p;
        p.x = this->x + k.x;
        p.y = this->y + k.y;
        p.theta_radian = this->theta_radian;
        p.theta_degree = this->theta_degree;
        p.update_position_vector();
        return p;
    }

    bool operator!=(const Position &k)
    {
        return (this->x == k.x) && (this->y == k.y);
    }

    friend std::ostream& operator<<(std::ostream& os, const Position &pos)
    {
        double x = pos.x;
        double y = pos.y;
        os << "(" << to_string(pos.x) << "," << to_string(pos.y) << "," << to_string(pos.theta_degree) << ")";
        return os;
    }

};

#endif