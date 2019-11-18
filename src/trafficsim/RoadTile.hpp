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
    bool isFlipped() const { return right_turn_; }

    void rotate();

    virtual void flip() = 0;
    virtual TileType getType() const = 0;
    virtual void connect(std::array<Tile *, 4> &neighbors) = 0;
    // Auto rotates road if there is neighbor, only RoadTurn has own implementation
    virtual void autoRotate(std::array<Tile *, 4> &neighbors);

    virtual bool connectableFrom(NeighborIndex n_index) const = 0;
    virtual bool canConnectTo(NeighborIndex n_index) const = 0;

protected:
    sf::Vector2f dir_;
    bool right_turn_ = true;

    void connectTo(Tile *another, NeighborIndex from);
};
} // namespace TrafficSim