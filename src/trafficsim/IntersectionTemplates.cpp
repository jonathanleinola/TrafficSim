#include "IntersectionTemplates.hpp"

namespace TrafficSim
{

std::vector<RoadInfo> CrossIntersection::indices_ = {
// idnex, dir       haslight    type        flipped     relative_pos
    {0, {0.f, -1.f}, true, StraightRoadType, false, {1, 0}},
    {0, {0.f, 1.f}, false, StraightRoadType, false, {2, 0}},

    {0, {-1.f, 0.f}, false, StraightRoadType, false, {0, 1}},
    {0, {0.f, -1.f}, false, IntersectionType, false, {1, 1}},
    {0, {-1.f, 0.f}, false, IntersectionType, false, {2, 1}},
    {0, {-1.f, 0.f}, true, StraightRoadType, false, {3, 1}},

    {0, {1.f, 0.f}, true, StraightRoadType, false, {0, 2}},
    {0, {1.f, 0.f}, false, IntersectionType, false, {1, 2}},
    {0, {0.f, 1.f}, false, IntersectionType, false, {2, 2}},
    {0, {1.f, 0.f}, false, StraightRoadType, false, {3, 2}},

    {0, {0.f, -1.f}, false, StraightRoadType, false, {1, 3}},
    {0, {0.f, 1.f}, true, StraightRoadType, false, {2, 3}},
};
}