#pragma once

#include "RoadTile.hpp"

namespace TrafficSim
{

class RoadJunction : public RoadTile
{
public:
    RoadJunction(const Tile &tile);

    virtual void flip();
    virtual TileType getType() const { return TileType::JunctionType; }
    virtual void connect(std::array<Tile *, 4> &neighbors);
    
    virtual bool connectableFrom(NeighborIndex n_index) const;
    virtual bool canConnectTo(NeighborIndex n_index) const;

    static void SetTextures(const sf::Texture *right_texture, const sf::Texture *left_texture);

private:
    const static sf::Texture *RightTexture;
    const static sf::Texture *LeftTexture;
};
} // namespace TrafficSim