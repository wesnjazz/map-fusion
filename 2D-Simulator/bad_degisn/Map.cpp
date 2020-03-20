#include "Map.h"
#include <iostream>

// Todo: Constructor

// Todo: check if it succeed to occupy
bool Map::occupy(Coordinate pos)
{
    map[pos] = 1;
    return true;
}

// Todo: check if it succeed to free
bool Map::free(Coordinate pos)
{
    map[pos] = 0;
    return true;
}

bool Map::is_occupied(Coordinate pos)
{
    return map[pos];
}

int Map::print_points()
{
    for (auto it = map.begin(); it != map.end(); ++it) {
        std::cout << "(" << it->first.x << "," << it->first.y << ")" << ":" << it->second << "\n";
    }
}