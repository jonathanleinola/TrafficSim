#include "RoadTrisection.hpp"


namespace TrafficSim
{

sf::Texture *RoadTrisection::RightTexture;
sf::Texture *RoadTrisection::LeftTexture;

RoadTrisection::RoadTrisection(const Tile &tile)
    : RoadTile(tile)
{
    rect_.setTexture(RoadTrisection::RightTexture);
}

void RoadTrisection::connect(std::array<Tile *, 4> &neighbors)
{
    if (dir_.y == 1)
    {
        connectTo(neighbors[NeighborIndex::UP], NeighborIndex::DOWN);
        if (right_turn_)
            connectTo(neighbors[NeighborIndex::RIGHT], NeighborIndex::LEFT);
        else
            connectTo(neighbors[NeighborIndex::LEFT], NeighborIndex::RIGHT);
    }

    else if (dir_.x == 1)
    {
        connectTo(neighbors[NeighborIndex::RIGHT], NeighborIndex::LEFT);
        if (right_turn_)
            connectTo(neighbors[NeighborIndex::DOWN], NeighborIndex::UP);
        else
            connectTo(neighbors[NeighborIndex::UP], NeighborIndex::DOWN);
    }

    else if (dir_.y == -1)
    {
        connectTo(neighbors[NeighborIndex::DOWN], NeighborIndex::UP);
        if (right_turn_)
            connectTo(neighbors[NeighborIndex::LEFT], NeighborIndex::RIGHT);
        else
            connectTo(neighbors[NeighborIndex::RIGHT], NeighborIndex::LEFT);
    }

    else if (dir_.x == -1)
    {
        connectTo(neighbors[NeighborIndex::LEFT], NeighborIndex::RIGHT);
        if (right_turn_)
            connectTo(neighbors[NeighborIndex::UP], NeighborIndex::DOWN);
        else
            connectTo(neighbors[NeighborIndex::DOWN], NeighborIndex::UP);
    }
}

bool RoadTrisection::connectableFrom(NeighborIndex n_index) const
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

void RoadTrisection::flip()
{
    if (right_turn_)
    {
        rect_.setTexture(RoadTrisection::LeftTexture);
    }
    else
    {
        rect_.setTexture(RoadTrisection::RightTexture);
    }
    dir_ = -dir_;
    right_turn_ = !right_turn_;
}

void RoadTrisection::SetTextures(sf::Texture *right_texture, sf::Texture *left_texture)
{
    RoadTrisection::RightTexture = right_texture;
    RoadTrisection::LeftTexture = left_texture;
}

} // namespace TrafficSim