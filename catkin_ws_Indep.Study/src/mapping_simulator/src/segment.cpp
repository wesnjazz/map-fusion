#include <iostream>
#include "segment.h"
using namespace std;


Segment::Segment(Vec2f p1, Vec2f p2)
{
    start = p1;
    end = p2;
    calculate_members();
}

Segment::Segment(Vec2f st, double length, double angle_degree)
{
    start = st;
    // cout << st;
    angle_radian = angle_degree * (M_PI / 180.0);
    double length_x = cos(angle_radian);
    double length_y = sin(angle_radian);
    if (fabs(length_x) < 0.00001) { length_x = 0.0; }
    if (fabs(length_y) < 0.00001) { length_y = 0.0; }
    double end_x = st.x() + length * length_x;
    double end_y = st.y() + length * length_y;
    end = Vec2f(end_x, end_y);
    calculate_members();
}

void Segment::calculate_members()
{
    segment = end - start;  // Get a vector of the line
    segment_unit = segment.normalized();    // Unit vector
    segment_norm_unit = segment.unitOrthogonal();   // Normal Unit vector
    remove_small_error_values(segment_unit);    // Replace very small number with zero
    remove_small_error_values(segment_norm_unit);

    x_diff = end.x()-start.x();     // Difference of x coordinate
    y_diff = end.y()-start.y();     // Difference of y coordinate
    angle_radian = atan2(y_diff, x_diff);  // Angle (Direction) of the line vector
    angle_degree = angle_radian * (180.0/M_PI);
    length = abs(sqrt((pow(x_diff,2.0) + pow(y_diff,2.0))));    // Length of the line
}


bool Segment::isParallel(const Segment &seg2)
{
    double dot_product = (segment_unit).dot(seg2.segment_norm_unit);     // Parallel if dot product is zero
    return (dot_product == 0.0) ? true : false;
}


bool Segment::ifIntersect(const Segment &seg2)
{
    // t: The distance on the segment line 1 to the intersecting point with segment 2
    // u: The distance on the segment line 2 to the intersecting point with segment 1
    // If t and u both are less or equal to itselves, then two line segments intersect!
    // if ((0.0 < t && t <= length)) {
    //     cout << "\t\tIntersect! at\n";
    // }
    // return (0.0 < t && t <= length);

    // if ((0.0 < t && t <= length) && (0.0 < seg2.t && seg2.t <= seg2.length)) {
    //     cout << "\t\tIntersect! at\n";
    // }
    return (0.0 < t && t <= length) &&
            (0.0 < seg2.t && seg2.t <= seg2.length);
}


Vec2f Segment::intersection_point(Segment &seg2)
{
    t = (seg2.start - start).dot(seg2.segment_norm_unit) / (segment_unit).dot(seg2.segment_norm_unit);
    seg2.t = (start - seg2.start).dot(segment_norm_unit) / (seg2.segment_unit).dot(segment_norm_unit);
    Vec2f intersect_vector = start + t*(segment_unit);
    // cout << "\nt:" << t << "\tu:" << seg2.t << "\n";
    remove_small_error_values(intersect_vector);
    return intersect_vector;
}

void Segment::remove_small_error_values(Vec2f &vec)
{
    if (fabs(vec.x()) < 0.00001) { vec = Vec2f(0, vec.y()); }    // Replace very small number with zero
    if (fabs(vec.y()) < 0.00001) { vec = Vec2f(vec.x(), 0); }
}