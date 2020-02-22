#ifndef MAP_H
#define MAP_H

#include <vector>
#include "segment.h"

struct Map
{
    Map();
    vector<Segment> segments;

    void add_segment(Segment seg);
};

#endif