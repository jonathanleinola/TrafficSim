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
    
    // Returns nullptr if there is no tile on that index
    Tile *getTile(unsigned int index);
    // Returns UINT_MAX if there is no tile on that index
    unsigned int getUpNeighbor(unsigned int index) const;
    unsigned int getRightNeighbor(unsigned int index) const;
    unsigned int getDownNeighbor(unsigned int index) const;
    unsigned int getLeftNeighbor(unsigned int index) const;

    unsigned int getTileCount() const { return tile_count_; }

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    static unsigned int GetIndex(unsigned int x, unsigned int y);

private:
    // tile_count_ x tile_count_ tile map
    constexpr static unsigned int tile_count_ = 100;
    std::array<std::unique_ptr<Tile>, tile_count_ * tile_count_> tiles_;

    float tile_size_;
};
} // namespace TrafficSim
