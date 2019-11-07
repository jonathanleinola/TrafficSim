#include "Intersection.hpp"

namespace TrafficSim
{

Intersection::Intersection(Road &road1, Road &road2, const sf::Vector2f& pos)
    : pos_(pos)
{
    road1.createIntersection(road2, pos_, intersectionNodes_);
    road2.createIntersection(road1, pos_, intersectionNodes_);

    // intersection nodes top left, top right, bot right, bot left.
    std::shared_ptr<Node> &tlNode = intersectionNodes_[0];
    std::shared_ptr<Node> &trNode = intersectionNodes_[1];
    std::shared_ptr<Node> &brNode = intersectionNodes_[2];
    std::shared_ptr<Node> &blNode = intersectionNodes_[3];


    tlNode->connect(blNode);
    blNode->connect(brNode);
    brNode->connect(trNode);
    trNode->connect(tlNode);

}

void Intersection::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (int i = 0; i < 4; ++i)
        target.draw(*(intersectionNodes_[i]), states);
}

} // namespace TrafSim
