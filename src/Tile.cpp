#include "Tile.hpp"

namespace TrafficSim
{
Tile::Tile(const sf::Vector2f &pos, float size, unsigned int tile_index)
    : pos_(pos), size_(size), rect_(sf::Vector2f(size, size)), tile_index_(tile_index)
{
    // Nice green color
    rect_.setPosition(pos_);
    rect_.setFillColor(sf::Color(119, 160, 93));
    rect_.setOutlineThickness(2.f);
    rect_.setOutlineColor(sf::Color(66, 107, 41));
    sf::Vector2f center = pos_ + sf::Vector2f(size_ / 2, size_ / 2);
    node_ = std::make_shared<Node>(center, sf::Color(66, 107, 41));
}

sf::Vector2f Tile::getCenter() const
{
    return pos_ + sf::Vector2f(size_ / 2, size_ / 2);
}


void Tile::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(rect_, states);
    target.draw(*node_, states);
}

} // namespace TrafficSim