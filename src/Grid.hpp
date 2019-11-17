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
    void init();

    void update(float delta_time);

    // Returns nullptr if there is no tile on that index
    std::unique_ptr<Tile> &getTile(unsigned int index);
    std::unique_ptr<Tile> &getTile(const sf::Vector2f &pos);
    // Returns UINT_MAX if there is no tile on that index
    std::unique_ptr<Tile> &getUpNeighbor(unsigned int index);
    std::unique_ptr<Tile> &getRightNeighbor(unsigned int index);
    std::unique_ptr<Tile> &getDownNeighbor(unsigned int index);
    std::unique_ptr<Tile> &getLeftNeighbor(unsigned int index);
    std::array<Tile*, 4> getNeigborTiles(unsigned int index);
    unsigned int getTileCount() const { return tile_count_; }
    unsigned int getSize() const { return tile_count_ * tile_count_; }   

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    static unsigned int GetTileIndex(unsigned int x, unsigned int y);

private:
    // tile_count_ x tile_count_ tile map
    constexpr static unsigned int tile_count_ = 50;
    std::array<std::unique_ptr<Tile>, tile_count_ * tile_count_> tiles_;
    std::unique_ptr<Tile> nulltile_ = nullptr;
    float tile_size_;
};
} // namespace TrafficSim
