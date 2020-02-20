#include "segment.h"


Segment::Segment(Vec2f p1, Vec2f p2)
{
    start = p1;
    end = p2;
    calculate_members();
}


void Segment::calculate_members()
{
    segment = end - start;
    segment_unit = segment.normalized();
    segment_unit_norm = segment.unitOrthogonal();
    x_diff = end.x()-start.x();
    y_diff = end.y()-start.y();
    angle = atan2(y_diff, x_diff);
    angle_degree = angle * (180.0/M_PI);
    length = abs(sqrt((pow(x_diff,2.0) + pow(y_diff,2.0))));
}


bool Segment::isParallel(const Segment &seg2)
{
    float dot_product = (this->segment_unit).dot(seg2.segment_unit_norm);
    cout << "isParallel(dot_product):" << dot_product << "\n";
    return (dot_product == 0.0) ? true : false;
}


bool Segment::ifIntersect(const Segment &seg2)
{
    return (0.0 < this->t && this->t <= this->length) &&
            (0.0 < seg2.t && seg2.t <= seg2.length);
}


Vec2f Segment::intersection_point(Segment &seg2)
{
    this->t = (seg2.start - this->start).dot(seg2.segment_unit_norm) / (this->segment_unit).dot(seg2.segment_unit_norm);
    seg2.t = (this->start - seg2.start).dot(this->segment_unit_norm) / (seg2.segment_unit).dot(this->segment_unit_norm);
    Vec2f intersect_vector = this->start + t*(this->segment_unit);

    cout << "t:" << t << "\n";
    cout << "u:" << seg2.t << "\n";
    // cout << "acrossb:\n" << acrossb << "\n";

    return intersect_vector;
}