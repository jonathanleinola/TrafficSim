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

    const std::unique_ptr<Tile> &getTile(unsigned int index) const;

    // Returns nullptr if there is no tile on that index
    const std::unique_ptr<Tile> &getUpNeighbor(unsigned int index) const;
    const std::unique_ptr<Tile> &getRightNeighbor(unsigned int index) const;
    const std::unique_ptr<Tile> &getDownNeighbor(unsigned int index) const;
    const std::unique_ptr<Tile> &getLeftNeighbor(unsigned int index) const;

    unsigned int getTileCount() const { return tile_count_; }

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    static unsigned int GetIndex(unsigned int x, unsigned int y);

private:
    // 20 x 20 tile map
    const static unsigned int tile_count_ = 20;
    std::array<std::unique_ptr<Tile>, tile_count_ * tile_count_> tiles_;

    float tile_size_;
};
} // namespace TrafficSim
