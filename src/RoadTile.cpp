#include "RoadTile.hpp"

namespace TrafficSim
{

sf::Texture RoadTile::Texture;

RoadTile::RoadTile(const Tile &tile)
    : Tile(tile.getPos(), tile.getSize(), tile.getTileIndex())
{
    rect_.setTexture(&RoadTile::Texture);
    rect_.setFillColor(sf::Color::White);
    rect_.setOutlineThickness(0.f);
    dir_ = sf::Vector2f(1, 0);
}

void RoadTile::SetTexture(const sf::Texture &texture)
{
    RoadTile::Texture = texture;
}

} // namespace TrafficSim