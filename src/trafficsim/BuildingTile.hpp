#pragma once

#include <array>
#include <climits> // UINT_MAX

#include <SFML/Graphics.hpp>

#include "Tile.hpp"
#include "TrafficLight.hpp"

namespace TrafficSim
{

enum BuildingType
{
    HomeBuildingType = 0,
    OfficeBildingType,

    // Keep last
    BuildingTypeCount
};

class BuildingTile : public Tile
{
public:
    BuildingTile(const Tile &tile);

    virtual BuildingType getType() const = 0;

    // Direction of the road
    // Up: { 0, 1 }, Right { 1, 0 }, Down { 0, -1 }, Left { -1, 0 }
    const sf::Vector2f &getDir() const { return dir_; }
    bool isFlipped() const { return right_turn_; }
   

    void rotate();
    virtual void flip();

    // Auto rotates road if there is neighbor, only RoadTurn has own implementation
    virtual void autoRotate(std::array<Tile *, 4> &neighbors);

    // Pure virtual functions
    virtual void connect(std::array<Tile *, 4> &neighbors) = 0;
    virtual bool connectableFrom(NeighborIndex n_index) const = 0;
    virtual bool canConnectTo(NeighborIndex n_index) const = 0;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

protected:
    // Up: { 0, 1 }, Right { 1, 0 }, Down { 0, -1 }, Left { -1, 0 }
    sf::Vector2f dir_;
    bool right_turn_ = true;
    void connectTo(Tile *another, NeighborIndex from);
};
} // namespace TrafficSim