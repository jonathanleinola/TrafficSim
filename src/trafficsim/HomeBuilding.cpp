#include "HomeBuilding.hpp"

#include <iostream>

namespace TrafficSim
{

const sf::Texture *HomeBuilding::Texture;

HomeBuilding::HomeBuilding(const Tile &tile)
    : BuildingTile(tile)
{
    rect_.setTexture(HomeBuilding::Texture);
}

void HomeBuilding::connect(std::array<Tile *, 4> &neighbors)
{
    if (dir_.y == 1)
        connectTo(neighbors[UP], DOWN);

    else if (dir_.x == 1)
        connectTo(neighbors[RIGHT], LEFT);

    else if (dir_.y == -1)
        connectTo(neighbors[DOWN], UP);

    else if (dir_.x == -1)
        connectTo(neighbors[LEFT], RIGHT);
}

bool HomeBuilding::canConnectTo(NeighborIndex n_index) const
{
    if (n_index == UP)
        return dir_.y == 1;

    else if (n_index == RIGHT)
        return dir_.x == 1;

    else if (n_index == DOWN)
        return dir_.y == -1;

    else if (n_index == LEFT)
        return dir_.x == -1;

    return false;
}

bool HomeBuilding::connectableFrom(NeighborIndex n_index) const
{
    if (n_index == UP)
        return dir_.y == -1;

    else if (n_index == RIGHT)
        return dir_.x == -1;

    else if (n_index == DOWN)
        return dir_.y == 1;

    else if (n_index == LEFT)
        return dir_.x == 1;

    return false;
}

void HomeBuilding::SetTexture(const sf::Texture *texture)
{
    HomeBuilding::Texture = texture;
}

} // namespace TrafficSim