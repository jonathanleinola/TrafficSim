#pragma once

#include <SFML/Graphics.hpp>

namespace TrafficSim
{
class Tile : public sf::Drawable
{
public:
    Tile(const sf::Vector2f &pos, float size);

    sf::Vector2f getCenter() const;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    sf::Vector2f pos_;
    float size_;
    sf::RectangleShape rect_;
};
} // namespace TrafficSim
