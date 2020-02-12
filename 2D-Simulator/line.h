#ifndef LINE_H
#define LINE_H

#include <iostream>
#include <Eigen/Core>
using namespace std;

struct Line
{
    Line(Eigen::Vector2f start, Eigen::Vector2f end)
    {
        p1 = start;
        p2 = end;
        calculate_members();
    }
    Eigen::Vector2f p1;
    Eigen::Vector2f p2;
    Eigen::Vector2f line_vector;
    double length;
    int orientation;

    void calculate_members()
    {
        length = abs(sqrt((pow((p2.x()-p1.x()),2.0) + pow((p2.y()-p1.y()),2.0))));
        line_vector = p2 - p1;
    }

    friend std::ostream& operator<<(std::ostream& os, const Line &l)
    {
        double x = l.p2.x()-l.p1.x();
        double x2 = pow(x,2.0);
        double y = l.p2.y()-l.p1.y();
        double y2 = pow(y,2.0);
        double z = sqrt(x2+y2);
        os << "[" << to_string(l.p1.x()) << "," << to_string(l.p1.y()) << "]";
        os << "->";
        os << "[" << to_string(l.p2.x()) << "," << to_string(l.p2.y()) << "]";
        os << "\tlength:" << l.length << "\torientation:";
        os << "\n" << l.line_vector;
        // os << "\n" << l.p2.x() << "-" << l.p1.x() << "=" << x << "\t" << x2;
        // os << "\n" << l.p2.y() << "-" << l.p1.y() << "=" << x << "\t" << y2;
        // os << "\t" << z << "\t" << abs(z);
        return os;
    }
};

#endif