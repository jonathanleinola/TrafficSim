#pragma once

#include "RoadTile.hpp"

namespace TrafficSim
{

class RoadTrisection : public RoadTile
{
public:
    RoadTrisection(const Tile &tile);

    virtual void flip();
    virtual TileType getType() const { return TileType::TrisectionType; }
    virtual void connect(std::array<Tile *, 4> &neighbors);
    
    virtual bool connectableFrom(NeighborIndex n_index) const;
    virtual bool canConnectTo(NeighborIndex n_index) const;

    static void SetTextures(const sf::Texture *right_texture, const sf::Texture *left_texture);

private:
    bool right_turn_ = true;
    const static sf::Texture *RightTexture;
    const static sf::Texture *LeftTexture;
};
} // namespace TrafficSim
