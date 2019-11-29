#pragma once

#include <SFML/Graphics.hpp>

#include "BuildingTile.hpp"

namespace TrafficSim
{

class OfficeBuilding : public BuildingTile
{
public:
    OfficeBuilding(const Tile &tile);
    virtual BuildingType getType() const { return BuildingType::OfficeBuildingType; }

    virtual void connect(std::array<Tile *, 4> &neighbors);

    virtual bool connectableFrom(NeighborIndex n_index) const;
    virtual bool canConnectTo(NeighborIndex n_index) const;

    static void SetTexture(const sf::Texture *texture);

private:
    const static sf::Texture *Texture;
};
} // namespace TrafficSim