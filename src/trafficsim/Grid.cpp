#include "Grid.hpp"
#include <climits>

namespace TrafficSim
{

Grid::Grid(float tile_size)
    : tile_size_(tile_size)
{
    /*
    *
    *   0,                  1,                      2,                      ..., tile_count_ - 1,
    *   
    *   tile_count_,        tile_count_ + 1,        tile_count_ + 2,        ..., tile_count_ * 2 - 1,
    * 
    *   tile_count_ * 2,    tile_count_ * 2 + 1,    tile_count_ * 2 + 2,    ..., tile_count_ * 3 - 1,
    * 
    * 
    */
   init();
}

void Grid::init()
{
    for (unsigned int i = 0; i < tile_count_; ++i)
    {
        for (unsigned int j = 0; j < tile_count_; ++j)
        {
            tiles_[i * tile_count_ + j] = std::make_unique<Tile>(Tile(sf::Vector2f(j * tile_size_, i * tile_size_), tile_size_, i * tile_count_ + j));
        }
    }
}

void Grid::update(float delta_time)
{
}

std::array<Tile *, 4> Grid::getNeigborTiles(unsigned int index)
{
    std::array<Tile *, 4> neighbors;
    neighbors[NeighborIndex::UP] = getUpNeighbor(index).get();
    neighbors[NeighborIndex::RIGHT] = getRightNeighbor(index).get();
    neighbors[NeighborIndex::DOWN] = getDownNeighbor(index).get();
    neighbors[NeighborIndex::LEFT] = getLeftNeighbor(index).get();
    return neighbors;
}

std::unique_ptr<Tile> &Grid::getTile(unsigned int index)
{
    if (index < tile_count_ * tile_count_)
        return tiles_[index];
    return nulltile_;
}

std::unique_ptr<Tile> &Grid::getTile(const sf::Vector2f &pos)
{
    if (pos.x < 0 || pos.y < 0 || pos.x > (tile_count_ * tile_size_) || pos.y > (tile_count_ * tile_size_))
        return nulltile_;

    int j = (pos.x + tile_size_) / tile_size_ - 1;
    int i = (pos.y + tile_size_) / tile_size_ - 1;
    return tiles_[i * tile_count_ + j];
}

std::unique_ptr<Tile> &Grid::getUpNeighbor(unsigned int index)
{
    if (index < tile_count_)
        return nulltile_;

    return tiles_[index - tile_count_];
}

std::unique_ptr<Tile> &Grid::getRightNeighbor(unsigned int index)
{
    if (index == 0 || (tile_count_ - 1) % index == 0)
        return nulltile_;

    return tiles_[index + 1];
}
std::unique_ptr<Tile> &Grid::getDownNeighbor(unsigned int index)
{
    if (index + tile_count_ >= tile_count_ * tile_count_)
        return nulltile_;

    return tiles_[index + tile_count_];
}
std::unique_ptr<Tile> &Grid::getLeftNeighbor(unsigned int index)
{
    if (index == 0 || (tile_count_) % index == 0)
        return nulltile_;

    return tiles_[index - 1];
}

void Grid::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (const auto &tile : tiles_)
        target.draw(*tile, states);
}

unsigned int Grid::GetTileIndex(unsigned int x, unsigned int y)
{
    return y * tile_count_ + x;
}

} // namespace TrafficSim