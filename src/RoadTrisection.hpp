#pragma once

#include "RoadTile.hpp"

namespace TrafficSim
{

class RoadTrisection : public RoadTile
{
public:
    RoadTrisection(const Tile &tile);

    virtual void flip();
    virtual TileType getType() const { return TileType::RoadTurnType; }
    virtual void connect(std::array<Tile *, 4> &neighbors);
    virtual bool connectableFrom(NeighborIndex n_index) const;
    virtual void connectTo(Tile *another, NeighborIndex from);

    static void SetTextures(const sf::Texture &right_texture, const sf::Texture &left_texture);

private:
    bool right_turn_ = true;
    static sf::Texture RightTexture;
    static sf::Texture LeftTexture;
};
} // namespace TrafficSim
