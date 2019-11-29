#pragma once

#include <SFML/Graphics.hpp>

#include "BuildingTile.hpp"

namespace TrafficSim
{

class HomeBuilding : public BuildingTile
{
public:
    HomeBuilding(const Tile &tile);
    virtual BuildingType getType() const { return BuildingType::HomeBuildingType; }

    virtual void connect(std::array<Tile *, 4> &neighbors);

    virtual bool connectableFrom(NeighborIndex n_index) const;
    virtual bool canConnectTo(NeighborIndex n_index) const;

    static void SetTexture(const sf::Texture *texture);

private:
    const static sf::Texture *Texture;
};
} // namespace TrafficSim