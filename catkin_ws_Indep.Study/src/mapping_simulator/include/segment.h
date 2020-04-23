#ifndef SEGMENT_H
#define SEGMENT_H

#include <string>
#include <Eigen/Dense>
#include <geometry_msgs/Vector3.h>
#include <vector_slam_msgs/LidarDisplayMsg.h>

typedef Eigen::Vector2f Vec2f;
typedef Eigen::Vector3f Vec3f;
typedef Eigen::Matrix2f Mat2f;
typedef Eigen::Matrix3f Mat3f;

using namespace std;


struct Segment
{
    Segment(Vec2f p1, Vec2f p2);
    Segment(Vec2f start, float length, float angle_degree);
    Vec2f start;                // start point vector
    Vec2f end;                  // end point vector
    Vec2f segment;              // segment(line) vector = end - start
    Vec2f segment_unit;         // unit vector of segment
    Vec2f segment_norm_unit;    // unit vector of normal vector of segment
    
    float t;                    // t in the parametric equation: a_vector = a_start + (a_direction) * t
    float x_diff;
    float y_diff;
    float angle_radian;
    float angle_degree;
    float length;

    void calculate_members();
    bool isParallel(const Segment &seg2);
    Vec2f intersection_point(Segment &seg2);
    bool ifIntersect(const Segment &seg2);
    void remove_small_error_values(Vec2f &vec);

    friend std::ostream& operator<<(std::ostream& os, const Segment &sg)
    {
        float x = sg.end.x()-sg.start.x();
        float x2 = pow(x,2.0);
        float y = sg.end.y()-sg.start.y();
        float y2 = pow(y,2.0);
        float z = sqrt(x2+y2);
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