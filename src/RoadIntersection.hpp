#pragma once

#include "RoadTile.hpp"

namespace TrafficSim
{

class RoadIntersection : public RoadTile
{
public:
    RoadIntersection(const Tile &tile);

    virtual void flip();
    virtual TileType getType() const { return TileType::IntersectionType; }
    virtual void connect(std::array<Tile *, 4> &neighbors);
    virtual bool connectableFrom(NeighborIndex n_index) const;

    static void SetTextures(sf::Texture *right_texture, sf::Texture *left_texture);

private:
    bool right_turn_ = true;
    static sf::Texture *RightTexture;
    static sf::Texture *LeftTexture;
};

} // namespace TrafficSim
