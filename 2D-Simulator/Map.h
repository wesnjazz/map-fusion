#ifndef MAP_H
#define MAP_H

#include <unordered_map>
#include <tuple>

struct Coordinate
{
    long x;
    long y;

    bool operator==(const Coordinate &p)
    {
        return x == p.x && y == p.y;
    }
};

struct Coordinate_hash
{
    std::size_t operator() (const Coordinate &c) const
    {
        return std::hash<long>()(c.x) ^ std::hash<long>()(c.y);
    }
};

class Map
{
private:
    std::unordered_map<Coordinate, bool, Coordinate_hash> map;
public:
    Map();

    bool occupy();
    bool free();
    bool is_occupied(int, int);
};

#endif