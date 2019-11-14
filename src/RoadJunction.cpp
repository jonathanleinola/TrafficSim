#include "RoadJunction.hpp"


namespace TrafficSim
{

sf::Texture *RoadJunction::RightTexture;
sf::Texture *RoadJunction::LeftTexture;

RoadJunction::RoadJunction(const Tile &tile)
    : RoadTile(tile)
{
    rect_.setTexture(RoadJunction::RightTexture);
}

void RoadJunction::connect(std::array<Tile *, 4> &neighbors)
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

bool RoadJunction::connectableFrom(NeighborIndex n_index) const
{
    if (n_index == NeighborIndex::UP)
        return dir_.y == -1 || (dir_.x == 1 && right_turn_) || (dir_.x == -1 && !right_turn_);

    else if (n_index == NeighborIndex::RIGHT)
        return dir_.x == -1 || (dir_.y == -1 && right_turn_) || (dir_.y == 1 && !right_turn_);

    else if (n_index == NeighborIndex::DOWN)
        return dir_.y == 1 || (dir_.x == -1 && right_turn_) || (dir_.x == 1 && !right_turn_);

    else if (n_index == NeighborIndex::LEFT)
        return dir_.x == 1 || (dir_.y == 1 && right_turn_) || (dir_.y == -1 && !right_turn_);

    return false;
}

void RoadJunction::flip()
{
    if (right_turn_)
    {
        rect_.setTexture(RoadJunction::LeftTexture);
    }
    else
    {
        rect_.setTexture(RoadJunction::RightTexture);
    }
    dir_ = -dir_;
    right_turn_ = !right_turn_;
}

void RoadJunction::SetTextures(sf::Texture *right_texture, sf::Texture *left_texture)
{
    RoadJunction::RightTexture = right_texture;
    RoadJunction::LeftTexture = left_texture;
}

} // namespace TrafficSim