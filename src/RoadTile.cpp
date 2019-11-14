#include "RoadTile.hpp"

namespace TrafficSim
{

RoadTile::RoadTile(const Tile &tile)
    : Tile(tile.getPos(), tile.getSize(), tile.getTileIndex()), dir_(1, 0)
{
    rect_.setFillColor(sf::Color::White);
    rect_.setOutlineThickness(0.f);
}

void RoadTile::rotate()
{
    dir_ = sf::Vector2f(dir_.y, -dir_.x);
    rect_.rotate(90);
}

} // namespace TrafficSim