#pragma once

#include <array>

#include <SFML/Graphics.hpp>

#include <Tile.hpp>

namespace TrafficSim
{
class Grid : public sf::Drawable
{
public:
    Grid(float tile_size);

    const Tile *getUpNeighbor() const;
    const Tile *getRightNeighbor() const;
    const Tile *getDownNeighbor() const;
    const Tile *getLeftNeighbor() const;

    unsigned int getTileCount() const { return tile_count_; }

    virtual void Node::draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    // 20 x 20 tile map
    const unsigned int tile_count_ = 20;
    std::array<Tile, grid_size_ * grid_size_> tiles_;

    float tile_size_;
};
} // namespace TrafficSim
