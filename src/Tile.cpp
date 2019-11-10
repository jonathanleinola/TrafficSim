#include "Tile.hpp"

namespace TrafficSim
{
Tile::Tile(const sf::Vector2f &pos, float size)
    : pos_(pos), size_(size), rect_(sf::Vector2f(size, size))
{
    rect_.setPosition(pos_);
    rect_.setFillColor(sf::Color::Cyan);
    rect_.setOutlineThickness(2.f);
    rect_.setOutlineColor(sf::Color::White);
}

sf::Vector2f Tile::getCenter() const
{
    return pos_ + {size_ / 2, size_ / 2};
}

void Tile::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(rect_, states);
}

} // namespace TrafficSim