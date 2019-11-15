#include "StraightRoad.hpp"


namespace TrafficSim
{

const sf::Texture *StraightRoad::Texture;

StraightRoad::StraightRoad(const Tile &tile)
    : RoadTile(tile)
{
    rect_.setTexture(StraightRoad::Texture);
}

void StraightRoad::connect(std::array<Tile *, 4> &neighbors)
{
    if (dir_.y == 1)
        connectTo(neighbors[NeighborIndex::UP], NeighborIndex::DOWN);

    else if (dir_.x == 1)
        connectTo(neighbors[NeighborIndex::RIGHT], NeighborIndex::LEFT);

    else if (dir_.y == -1)
        connectTo(neighbors[NeighborIndex::DOWN], NeighborIndex::UP);

    else if (dir_.x == -1)
        connectTo(neighbors[NeighborIndex::LEFT], NeighborIndex::RIGHT);
}

bool StraightRoad::connectableFrom(NeighborIndex n_index) const
{
    if (n_index == NeighborIndex::UP)
        return dir_.y == -1;

    else if (n_index == NeighborIndex::RIGHT)
        return dir_.x == -1;

    else if (n_index == NeighborIndex::DOWN)
        return dir_.y == 1;

    else if (n_index == NeighborIndex::LEFT)
        return dir_.x == 1;

    return false;
}

void StraightRoad::flip()
{
    rotate();
    rotate();
}

void StraightRoad::SetTexture(const sf::Texture *texture)
{
    StraightRoad::Texture = texture;
}

} // namespace TrafficSim