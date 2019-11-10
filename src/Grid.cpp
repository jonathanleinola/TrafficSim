#include "Grid.hpp"

namespace TrafficSim
{

Grid::Grid(float tile_size)
    : tile_size_(tile_size)
{
    for (int i = 0; i < tile_count_; ++i)
    {
        for (int j = 0; j < tile_count_; ++j)
        {
            tiles_[i * tile_count_ + j] = sf::Vector2f(j * tile_size_, i * tile_size_), tile_size_);
        }
    }
}

const Tile *Grid::getUpNeighbor() const
{
}
const Tile *Grid::getRightNeighbor() const
{
}
const Tile *Grid::getDownNeighbor() const
{
}
const Tile *Grid::getLeftNeighbor() const
{
}

void Grid::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (const auto &tile : tiles_)
        target.draw(tile, states);
}

} // namespace TrafficSim