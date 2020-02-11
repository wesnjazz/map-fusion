#ifndef MAP_H
#define MAP_H

#include <unordered_map>
#include <sstream>

/**
 * Coordinate struct
 * (x, y) position
 **/
struct Coordinate
{
    long x;
    long y;

    Coordinate(long x, long y) { this->x = x; this->y = y; };

    bool operator==(const Coordinate &c) const
    {
        return x == c.x && y == c.y;
    }

    // int operator<<(const Coordinate &c) const
    // {
        // return c.x;
    // }

    // std::ostream& operator<<(std::ostream& os) 
    // {
    //     std::stringstream ss;
    //     os << this->x << "," << this->y;
        
    //     return os;
    //     // return ss.str();
    // }
};

// Todo: overload << operator to pass its coordiantes as a string

// std::ostream& operator<<(std::ostream& os, const Coordinate &c)
// {
    // os << c.x << "," << c.y;
// }

// Custom hash function of "Coordinate" struct
class Coordinate_hash
{
public:
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
    Map() { ; };
    bool occupy(Coordinate pos);
    bool free(Coordinate pos);
    bool is_occupied(Coordinate pos);
    int print_points();
};


#endif