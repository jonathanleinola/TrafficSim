#include "RoadTile.hpp"

#include <iostream>

namespace TrafficSim
{

RoadTile::RoadTile(const Tile &tile)
    : Tile(tile.getPos(), tile.getSize(), tile.getTileIndex()), dir_(1, 0)
{
    rect_.setFillColor(sf::Color::White);
    rect_.setOutlineThickness(0.f);
}

void RoadTile::connectTo(Tile *another, NeighborIndex from)
{
    if (!another || another->getType() == TileType::Empty)
        return;

    RoadTile *road_tile = static_cast<RoadTile *>(another);
    if (road_tile->connectableFrom(from))
    {
        this->node_->connect(road_tile->getNode());
        std::cout << "Connected" << std::endl;
    }
}

void RoadTile::rotate()
{
    dir_ = sf::Vector2f(dir_.y, -dir_.x);
    rect_.rotate(90);
}

} // namespace TrafficSim