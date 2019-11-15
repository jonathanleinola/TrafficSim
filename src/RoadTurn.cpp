#include "RoadTurn.hpp"

namespace TrafficSim
{

const sf::Texture *RoadTurn::RightTexture;
const sf::Texture *RoadTurn::LeftTexture;

RoadTurn::RoadTurn(const Tile &tile)
    : RoadTile(tile)
{
    rect_.setTexture(RoadTurn::RightTexture);
}

void RoadTurn::connect(std::array<Tile *, 4> &neighbors)
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

bool RoadTurn::connectableFrom(NeighborIndex n_index) const
{
    if (right_turn_)
    {
        if (n_index == NeighborIndex::UP)
            return dir_.x == -1;

        else if (n_index == NeighborIndex::RIGHT)
            return dir_.y == 1;

        else if (n_index == NeighborIndex::DOWN)
            return dir_.x == 1;

        else if (n_index == NeighborIndex::LEFT)
            return dir_.y == -1;
    }
    else
    {
        if (n_index == NeighborIndex::UP)
            return dir_.x == 1;

        else if (n_index == NeighborIndex::RIGHT)
            return dir_.y == -1;

        else if (n_index == NeighborIndex::DOWN)
            return dir_.x == -1;

        else if (n_index == NeighborIndex::LEFT)
            return dir_.y == 1;
    }

    return false;
}

void RoadTurn::flip()
{
    if (right_turn_)
    {
        rect_.setTexture(RoadTurn::LeftTexture);
    }
    else
    {
        rect_.setTexture(RoadTurn::RightTexture);
    }
    dir_ = -dir_;
    right_turn_ = !right_turn_;
}

void RoadTurn::SetTextures(const sf::Texture *right_texture, const sf::Texture *left_texture)
{
    RoadTurn::RightTexture = right_texture;
    RoadTurn::LeftTexture = left_texture;
}

} // namespace TrafficSim