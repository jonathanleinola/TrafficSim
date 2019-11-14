#pragma once

#include <SFML/Graphics.hpp>
#include <array>
#include "Tile.hpp"

namespace TrafficSim
{
class RoadTile : public Tile
{
public:
    RoadTile(const Tile &tile);

    const sf::Vector2f &getDir() const { return dir_; }

    void rotate();

    virtual void flip() = 0;
    virtual TileType getType() const = 0;
    virtual void connect(std::array<Tile *, 4> &neighbors) = 0;
    virtual bool connectableFrom(NeighborIndex n_index) const = 0;

protected:
    sf::Vector2f dir_;
    virtual void connectTo(Tile *another, NeighborIndex from) = 0;
};
} // namespace TrafficSim