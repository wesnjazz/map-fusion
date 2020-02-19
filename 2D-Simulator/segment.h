#ifndef SEGMENT_H
#define SEGMENT_H

#include <iostream>
#include <math.h>
#include <Eigen/Dense>

using namespace std;
typedef Eigen::Vector2f Vec2f;
typedef Eigen::Hyperplane<float, 2> Line;

// For accurate comparison between floats
// bool cmpf(float A, float B, float epsilon = 0.005f)
// {
//     return (fabs(A - B) < epsilon);
// }

struct Segment
{
    Segment(Vec2f start, Vec2f end);
    Vec2f p1;
    Vec2f p2;
    Line segment;
    float x_difference;
    float y_difference;
    float angle;
    float angle_degree;
    float length;

    void calculate_members();
    Vec2f intersect(const Segment &seg2);
    Vec2f intersect2(const Segment &seg2);

    friend std::ostream& operator<<(std::ostream& os, const Segment &sg)
    {
        float x = sg.p2.x()-sg.p1.x();
        float x2 = pow(x,2.0);
        float y = sg.p2.y()-sg.p1.y();
        float y2 = pow(y,2.0);
        float z = sqrt(x2+y2);
        os << "[" << to_string(sg.p1.x()) << "," << to_string(sg.p1.y()) << "]";
        os << "->";
        os << "[" << to_string(sg.p2.x()) << "," << to_string(sg.p2.y()) << "]";
        os << "\tlength:" << sg.length << "\tangle:" << sg.angle << "\tangle_degree:" << sg.angle_degree;
        // os << "\n" << sg.p1.se;
        // os << "\n" << sg.segment;
        // os << "\n" << sg.p2.x() << "-" << sg.p1.x() << "=" << x << "\t" << x2;
        // os << "\n" << sg.p2.y() << "-" << sg.p1.y() << "=" << x << "\t" << y2;
        // os << "\t" << z << "\t" << abs(z);
        return os;
    }
};

#endif