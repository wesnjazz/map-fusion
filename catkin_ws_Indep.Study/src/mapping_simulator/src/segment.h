#ifndef SEGMENT_H
#define SEGMENT_H

#include <string>
#include <Eigen/Dense>
#include <geometry_msgs/Vector3.h>
typedef Eigen::Vector2f Vec2f;
using namespace std;


struct Segment
{
    Segment(Vec2f p1, Vec2f p2);
    Segment(Vec2f start, double length, double angle_degree);
    Vec2f start;                // start point vector
    Vec2f end;                  // end point vector
    Vec2f segment;              // segment(line) vector = end - start
    Vec2f segment_unit;         // unit vector of segment
    Vec2f segment_norm_unit;    // unit vector of normal vector of segment
    
    double t;                    // t in the parametric equation: a_vector = a_start + (a_direction) * t
    double x_diff;
    double y_diff;
    double angle_radian;
    double angle_degree;
    double length;

    void calculate_members();
    bool isParallel(const Segment &seg2);
    Vec2f intersection_point(Segment &seg2);
    bool ifIntersect(const Segment &seg2);
    void remove_small_error_values(Vec2f &vec);

    friend std::ostream& operator<<(std::ostream& os, const Segment &sg)
    {
        double x = sg.end.x()-sg.start.x();
        double x2 = pow(x,2.0);
        double y = sg.end.y()-sg.start.y();
        double y2 = pow(y,2.0);
        double z = sqrt(x2+y2);
        os << "[" << to_string(sg.start.x()) << "," << to_string(sg.start.y()) << "]";
        os << "->";
        os << "[" << to_string(sg.end.x()) << "," << to_string(sg.end.y()) << "]";
        os << "\tlength:" << sg.length << "\tangle:" << sg.angle_radian << "\tangle_degree:" << sg.angle_degree;
        return os;
    }
};


struct compare_xy_Vec2f {
    bool operator ()(const Vec2f &a, const Vec2f &b) const {
        return (a.x() == b.x() ? a.y() < b.y() : a.x() < b.x());
    }
};


struct compare_xy_Vec3 {
    bool operator ()(const geometry_msgs::Vector3 &a, const geometry_msgs::Vector3 &b) const {
        return (a.x == b.x ? a.y < b.y : a.x < b.x);
    }
};


#endif