#pragma once

#include <array>
#include <climits> // UINT_MAX

#include <SFML/Graphics.hpp>

#include "Tile.hpp"
#include "TrafficLight.hpp"

namespace TrafficSim
{
class RoadTile : public Tile
{
public:
    RoadTile(const Tile &tile);

    const sf::Vector2f &getDir() const { return dir_; }
    bool isFlipped() const { return right_turn_; }
    TrafficLight *getLight() { return light_.get(); }

    void rotate();
    virtual void flip();
    void addLight(unsigned int handler_id);
    unsigned int removeLight();

    virtual TileType getType() const = 0;
    virtual void connect(std::array<Tile *, 4> &neighbors) = 0;
    // Auto rotates road if there is neighbor, only RoadTurn has own implementation
    virtual void autoRotate(std::array<Tile *, 4> &neighbors);

    virtual bool connectableFrom(NeighborIndex n_index) const = 0;
    virtual bool canConnectTo(NeighborIndex n_index) const = 0;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

protected:
    // Up: { 0, 1 }, Right { 1, 0 }, Down { 0, -1 }, Left { -1, 0 }
    sf::Vector2f dir_;
    bool right_turn_ = true;
    std::unique_ptr<TrafficLight> light_ = nullptr;

    void connectTo(Tile *another, NeighborIndex from);
};
} // namespace TrafficSim