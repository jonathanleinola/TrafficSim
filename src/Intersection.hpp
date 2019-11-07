#pragma once

#include "Road.hpp"

namespace TrafficSim
{
class Intersection : public sf::Drawable
{
public:
    Intersection(Road &road1, Road &road2, const sf::Vector2f& pos);

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    const sf::Vector2f pos_;

    std::shared_ptr<Node> intersectionNodes_[4];
};
} // namespace TrafSim
