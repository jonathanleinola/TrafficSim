#include "IntersectionTemplates.hpp"

namespace TrafficSim
{

std::vector<RoadInfo> IntersectionTemplates::cross_intersection_indices_ = {
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

std::vector<RoadInfo> IntersectionTemplates::t_intersection_down_indices_ = {
    // idnex, dir       haslight    type        flipped     relative_pos
    {0, {-1.f, 0.f}, false, StraightRoadType, false, {0, 1}},
    {0, {1.f, 0.f}, false, TrisectionType, true, {1, 1}},
    {0, {1.f, 0.f}, false, JunctionType, true, {2, 1}},
    {0, {-1.f, 0.f}, true, StraightRoadType, false, {3, 1}},

    {0, {1.f, 0.f}, true, StraightRoadType, false, {0, 2}},
    {0, {1.f, 0.f}, false, IntersectionType, false, {1, 2}},
    {0, {0.f, 1.f}, false, IntersectionType, false, {2, 2}},
    {0, {1.f, 0.f}, false, StraightRoadType, false, {3, 2}},

    {0, {0.f, -1.f}, false, StraightRoadType, false, {1, 3}},
    {0, {0.f, 1.f}, true, StraightRoadType, false, {2, 3}},
};

std::vector<RoadInfo> IntersectionTemplates::t_intersection_up_indices_ = {
    // idnex, dir       haslight    type        flipped     relative_pos
    {0, {0.f, -1.f}, true, StraightRoadType, false, {1, 0}},
    {0, {0.f, 1.f}, false, StraightRoadType, false, {2, 0}},

    {0, {-1.f, 0.f}, false, StraightRoadType, false, {0, 1}},
    {0, {0.f, -1.f}, false, IntersectionType, false, {1, 1}},
    {0, {-1.f, 0.f}, false, IntersectionType, false, {2, 1}},
    {0, {-1.f, 0.f}, true, StraightRoadType, false, {3, 1}},

    {0, {1.f, 0.f}, true, StraightRoadType, false, {0, 2}},
    {0, {-1.f, 0.f}, false, JunctionType, true, {1, 2}},
    {0, {-1.f, 0.f}, false, TrisectionType, true, {2, 2}},
    {0, {1.f, 0.f}, false, StraightRoadType, false, {3, 2}},

};

std::vector<RoadInfo> IntersectionTemplates::t_intersection_left_indices_ = {
    // idnex, dir       haslight    type        flipped     relative_pos
    {0, {0.f, -1.f}, true, StraightRoadType, false, {1, 0}},
    {0, {0.f, 1.f}, false, StraightRoadType, false, {2, 0}},

    {0, {-1.f, 0.f}, false, StraightRoadType, false, {0, 1}},
    {0, {0.f, -1.f}, false, IntersectionType, false, {1, 1}},
    {0, {0.f, -1.f}, false, TrisectionType, true, {2, 1}},

    {0, {1.f, 0.f}, true, StraightRoadType, false, {0, 2}},
    {0, {1.f, 0.f}, false, IntersectionType, false, {1, 2}},
    {0, {0.f, -1.f}, false, JunctionType, true, {2, 2}},

    {0, {0.f, -1.f}, false, StraightRoadType, false, {1, 3}},
    {0, {0.f, 1.f}, true, StraightRoadType, false, {2, 3}},
};

std::vector<RoadInfo> IntersectionTemplates::t_intersection_right_indices_ = {
    // idnex, dir       haslight    type        flipped     relative_pos
    {0, {0.f, -1.f}, true, StraightRoadType, false, {0, 0}},
    {0, {0.f, 1.f}, false, StraightRoadType, false, {1, 0}},

    {0, {0.f, 1.f}, false, JunctionType, true, {0, 1}},
    {0, {-1.f, 0.f}, false, IntersectionType, false, {1, 1}},
    {0, {-1.f, 0.f}, true, StraightRoadType, false, {2, 1}},

    {0, {0.f, 1.f}, false, TrisectionType, true, {0, 2}},
    {0, {0.f, 1.f}, false, IntersectionType, false, {1, 2}},
    {0, {1.f, 0.f}, false, StraightRoadType, false, {2, 2}},

    {0, {0.f, -1.f}, false, StraightRoadType, false, {0, 3}},
    {0, {0.f, 1.f}, true, StraightRoadType, false, {1, 3}},
};
} // namespace TrafficSim