#include "segment.h"


Segment::Segment(Vec2f p1, Vec2f p2)
{
    start = p1;
    end = p2;
    calculate_members();
}

Segment::Segment(Vec2f st, float length, float angle_degree)
{
    start = st;
    float angle_radian = angle_degree * (M_PI / 180.0);
    float end_x = st.x() + length * cos(angle_radian);
    float end_y = st.y() + length * sin(angle_radian);
    end = Vec2f(end_x, end_y);
    calculate_members();
}

void Segment::calculate_members()
{
    segment = end - start;  // Get a vector of the line
    segment_unit = segment.normalized();    // Unit vector
    remove_small_error_values(segment_unit);
    // if (fabs(segment_unit.x()) < 0.00001) { segment_unit = Vec2f(0, segment_unit.y()); }    // Replace very small number with zero
    // if (fabs(segment_unit.y()) < 0.00001) { segment_unit = Vec2f(segment_unit.x(), 0); }
    segment_norm_unit = segment.unitOrthogonal();   // Normal Unit vector
    remove_small_error_values(segment_norm_unit);
    // if (fabs(segment_norm_unit.x()) < 0.00001) { segment_norm_unit = Vec2f(0, segment_norm_unit.y()); }
    // if (fabs(segment_norm_unit.y()) < 0.00001) { segment_norm_unit = Vec2f(segment_norm_unit.x(), 0); }

    x_diff = end.x()-start.x();     // Difference of x coordinate
    y_diff = end.y()-start.y();     // Difference of y coordinate
    angle_radian = atan2(y_diff, x_diff);  // Angle (Direction) of the line vector
    angle_degree = angle_radian * (180.0/M_PI);
    length = abs(sqrt((pow(x_diff,2.0) + pow(y_diff,2.0))));    // Length of the line
}


bool Segment::isParallel(const Segment &seg2)
{
    float dot_product = (segment_unit).dot(seg2.segment_norm_unit);     // Parallel if dot product is zero
    return (dot_product == 0.0) ? true : false;
}


bool Segment::ifIntersect(const Segment &seg2)
{
    // t: The distance on the segment line 1 to the intersecting point with segment 2
    // u: The distance on the segment line 2 to the intersecting point with segment 1
    // If t and u both are less or equal to itselves, then two line segments intersect!
    if ((0.0 < t && t <= length) && (0.0 < seg2.t && seg2.t <= seg2.length)) {
        cout << "\t\tIntersect! at\n";
    }
    return (0.0 < t && t <= length) &&
            (0.0 < seg2.t && seg2.t <= seg2.length);
}


Vec2f Segment::intersection_point(Segment &seg2)
{
    t = (seg2.start - start).dot(seg2.segment_norm_unit) / (segment_unit).dot(seg2.segment_norm_unit);
    seg2.t = (start - seg2.start).dot(segment_norm_unit) / (seg2.segment_unit).dot(segment_norm_unit);
    Vec2f intersect_vector = start + t*(segment_unit);
    remove_small_error_values(intersect_vector);
    return intersect_vector;
}

void Segment::remove_small_error_values(Vec2f &vec)
{
    if (fabs(vec.x()) < 0.00001) { vec = Vec2f(0, vec.y()); }    // Replace very small number with zero
    if (fabs(vec.y()) < 0.00001) { vec = Vec2f(vec.x(), 0); }
}