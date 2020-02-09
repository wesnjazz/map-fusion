#ifndef MAP_H
#define MAP_H

#include <unordered_map>
#include <tuple>

class Map
{
private:
    // std::unordered_map<std::tuple<int, int>, bool> map;
public:
    Map();

    bool occupy();
    bool free();
    bool is_occupied(int, int);
};

#endif