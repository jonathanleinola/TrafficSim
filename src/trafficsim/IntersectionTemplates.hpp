#pragma once

#include <vector>
#include <iostream>

#include "StraightRoad.hpp"
#include "RoadIntersection.hpp"
#include "RoadJunction.hpp"
#include "RoadTrisection.hpp"

namespace TrafficSim
{

enum TemplateType
{
    CrossIntersectionType = 0,
    TIntersectionType,

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

class IntersectionTemplates
{
public:
    static std::vector<RoadInfo> GetTiles(TemplateType type, unsigned int index, unsigned int map_side_count)
    {
        if (type == CrossIntersectionType)
        {
            for (unsigned int i = 0; i < cross_intersection_indices_.size(); ++i)
            {
                cross_intersection_indices_[i].index = index + (cross_intersection_indices_[i].relative_pos.x - 1) + (cross_intersection_indices_[i].relative_pos.y - 2) * map_side_count;
            }
            return cross_intersection_indices_;
        }
        else if (type == TIntersectionType)
        {
            for (unsigned int i = 0; i < t_intersection_indices_.size(); ++i)
            {
                t_intersection_indices_[i].index = index + (t_intersection_indices_[i].relative_pos.x - 1) + (t_intersection_indices_[i].relative_pos.y - 2) * map_side_count;
            }
            return t_intersection_indices_;
        }

        return cross_intersection_indices_;
    }
    static bool CanPlace(TemplateType type, unsigned int index, unsigned int map_side_count)
    {
        if (type == CrossIntersectionType)
        {
            if (index < map_side_count * 2)
                return false;
            if (index > map_side_count * (map_side_count - 1))
                return false;
            if (index % map_side_count >= map_side_count - 2)
                return false;
            if (index % map_side_count == 0)
                return false;
        }
        if (type == TIntersectionType)
        {
            if (index < map_side_count)
                return false;
            if (index > map_side_count * (map_side_count - 1))
                return false;
            if (index % map_side_count >= map_side_count - 2)
                return false;
            if (index % map_side_count == 0)
                return false;
        }
        return true;
    }

private:
    static std::vector<RoadInfo> cross_intersection_indices_;
    static std::vector<RoadInfo> t_intersection_indices_;
};

} // namespace TrafficSim