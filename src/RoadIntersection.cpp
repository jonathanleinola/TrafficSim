#include "RoadIntersection.hpp"


namespace TrafficSim
{

const sf::Texture *RoadIntersection::RightTexture;
const sf::Texture *RoadIntersection::LeftTexture;

RoadIntersection::RoadIntersection(const Tile &tile)
    : RoadTile(tile)
{
    rect_.setTexture(RoadIntersection::RightTexture);
}

void RoadIntersection::connect(std::array<Tile *, 4> &neighbors)
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

bool RoadIntersection::connectableFrom(NeighborIndex n_index) const
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

void RoadIntersection::flip()
{
    if (right_turn_)
    {
        rect_.setTexture(RoadIntersection::LeftTexture);
    }
    else
    {
        rect_.setTexture(RoadIntersection::RightTexture);
    }
    dir_ = -dir_;
    right_turn_ = !right_turn_;
}

void RoadIntersection::SetTextures(const sf::Texture *right_texture, const sf::Texture *left_texture)
{
    RoadIntersection::RightTexture = right_texture;
    RoadIntersection::LeftTexture = left_texture;
}

} // namespace TrafficSim