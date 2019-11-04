#pragma once

#include "Road.hpp"

namespace TrafficSim
{
class Intersection : public sf::Drawable
{
public:
    Intersection(const std::shared_ptr<Road> &road1, const std::shared_ptr<Road> &road2, const sf::Vector2f& pos);

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    const sf::Vector2f pos_;

    std::pair<std::shared_ptr<Road>, std::shared_ptr<Road>> roads_;
    std::shared_ptr<Node> intersectionNodes_[4];
};
} // namespace TrafSim
