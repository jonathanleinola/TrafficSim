#pragma once

#include <SFML/Graphics.hpp>

#include "Tile.hpp"

namespace TrafficSim
{
class RoadTile : public Tile
{
public:
    RoadTile(const Tile &tile);
    
    static void SetTexture(const sf::Texture &texture);

    virtual TileType getType() const { return TileType::RoadType; }

private:
    static sf::Texture Texture;
};
} // namespace TrafficSim