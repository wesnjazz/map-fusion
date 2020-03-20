#include "Map.h"
#include <iostream>

int main(int argc, char **argv)
{
    Map map;

    map.occupy(Coordinate(0,0));
    map.occupy(Coordinate(1,1));
    map.occupy(Coordinate(2,2));
    
    map.print_points();
    std::cout << map.is_occupied(Coordinate(2,2)) << "\n";
    std::cout << map.is_occupied(Coordinate(2,1)) << "\n";

    return 0;
}