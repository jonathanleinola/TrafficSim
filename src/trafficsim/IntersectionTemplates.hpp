#pragma once

#include <vector>
#include <iostream>

#include "StraightRoad.hpp"
#include "RoadINtersection.hpp"
#include "RoadJunction.hpp"
#include "RoadTrisection.hpp"

namespace TrafficSim
{


enum TemplateType
{
    CrossIntersectionType = 0,

    TemplateTypeCount,
};

struct RoadInfo
{
    RoadInfo(int index, sf::Vector2f dir, bool hasLight, RoadType type, bool flipped, sf::Vector2i rel) : index(index), dir(dir), hasLight(hasLight), type(type), flipped(flipped), relative_pos(rel){};

    unsigned int index;
    sf::Vector2f dir;
    bool hasLight;
    RoadType type;
    bool flipped;
    sf::Vector2i relative_pos;
};

class CrossIntersection
{
public:
    static std::vector<RoadInfo> GetTiles(unsigned int index, unsigned int map_side_count)
    {
        for (unsigned int i = 0; i < indices_.size(); ++i)
        {
            indices_[i].index = index + (indices_[i].relative_pos.x - 1) + (indices_[i].relative_pos.y - 2) * map_side_count;
        }
        return indices_;
    }
    static bool CanPlace(unsigned int index, unsigned int map_side_count)
    {
        if (index < map_side_count * 2)
            return false;
        if (index > map_side_count * (map_side_count - 1))
            return false;
        if (index % map_side_count >= map_side_count - 2)
            return false;
        if(index % map_side_count == 0)
            return false;
        return true;
    }

private:
    static std::vector<RoadInfo> indices_;
};

} // namespace TrafficSim