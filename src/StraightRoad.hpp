#pragma once

#include <SFML/Graphics.hpp>

#include "RoadTile.hpp"

namespace TrafficSim
{

class StraightRoad : public RoadTile
{
public:
    StraightRoad(const Tile &tile);

    virtual void flip();
    virtual TileType getType() const { return TileType::StraightRoadType; }
    virtual void connect(std::array<Tile *, 4> &neighbors);
    virtual bool connectableFrom(NeighborIndex n_index) const;

    static void SetTexture(sf::Texture * texture);

private:
    static sf::Texture *Texture;
};
} // namespace TrafficSim