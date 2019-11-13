#include "Grid.hpp"

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
    for (int i = 0; i < tile_count_; ++i)
    {
        for (int j = 0; j < tile_count_; ++j)
        {
            tiles_[i * tile_count_ + j] = std::make_unique<Tile>(Tile(sf::Vector2f(j * tile_size_, i * tile_size_), tile_size_, i * tile_count_ + j));
        }
    }
}

Tile *Grid::getTile(unsigned int index)
{
    if(index < tile_count_ * tile_count_)
        return tiles_[index].get();
    return nullptr;
}

unsigned int Grid::getUpNeighbor(unsigned int index) const
{
    if (index < tile_count_)
        return UINT_MAX;
    else
        return index - tile_count_;
}

unsigned int Grid::getRightNeighbor(unsigned int index) const
{
    if ((tile_count_ - 1) % index == 0)
        return UINT_MAX;
    else
        return index + 1;
}
unsigned int Grid::getDownNeighbor(unsigned int index) const
{
    if (index + tile_count_ <= tile_count_ * tile_count_)
        return UINT_MAX;
    else
        return index + tile_count_;
}
unsigned int Grid::getLeftNeighbor(unsigned int index) const
{
    if ((tile_count_) % index == 0)
        return UINT_MAX;
    else
        return index - 1;
}

void Grid::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (const auto &tile : tiles_)
        target.draw(*tile, states);
}

unsigned int Grid::GetIndex(unsigned int x, unsigned int y)
{
    return y * tile_count_ + x;
}

} // namespace TrafficSim