#include "HomeBuilding.hpp"

#include <iostream>

namespace TrafficSim
{

const sf::Texture *HomeBuilding::Texture;

HomeBuilding::HomeBuilding(const Tile &tile)
    : BuildingTile(tile)
{
    rect_.setTexture(HomeBuilding::Texture);
}

void HomeBuilding::SetTexture(const sf::Texture *texture)
{
    HomeBuilding::Texture = texture;
}

} // namespace TrafficSim