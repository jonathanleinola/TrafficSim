#include "BuildingTile.hpp"

#include <iostream>

namespace TrafficSim
{

BuildingTile::BuildingTile(const Tile &tile)
    : Tile(tile.getPos(), tile.getSize(), tile.getTileIndex()), dir_(1, 0)
{
    rect_.setFillColor(sf::Color::White);
    rect_.setOutlineThickness(0.f);
}

/*
void BuildingTile::addLight(unsigned int handler_id)
{
    light_ = std::make_unique<TrafficLight>(pos_, dir_, size_, handler_id);
}

unsigned int BuildingTile::removeLight()
{
    unsigned int handler_id = UINT_MAX;
    if (light_)
        handler_id = light_->getHandlerId();
    light_ = nullptr;
    return handler_id;
}
*/
void BuildingTile::autoRotate(std::array<Tile *, 4> &neighbors)
{
    if (neighbors[LEFT] && neighbors[LEFT]->getCategory() == TileCategory::RoadCategory)
    {
        BuildingTile *r = static_cast<BuildingTile *>(neighbors[LEFT]);
        if (r->canConnectTo(RIGHT))
            return;
    }
    if (neighbors[UP] && neighbors[UP]->getCategory() == TileCategory::RoadCategory)
    {
        BuildingTile *r = static_cast<BuildingTile *>(neighbors[UP]);
        if (r->canConnectTo(DOWN))
        {
            rotate();
            return;
        }
    }
    if (neighbors[RIGHT] && neighbors[RIGHT]->getCategory() == TileCategory::RoadCategory)
    {
        BuildingTile *r = static_cast<BuildingTile *>(neighbors[RIGHT]);
        if (r->canConnectTo(LEFT))
        {
            flip();
            return;
        }
    }
    if (neighbors[DOWN] && neighbors[DOWN]->getCategory() == TileCategory::RoadCategory)
    {
        BuildingTile *r = static_cast<BuildingTile *>(neighbors[DOWN]);
        if (r->canConnectTo(UP))
        {
            rotate();
            flip();
            return;
        }
    }
}

void BuildingTile::connectTo(Tile *another, NeighborIndex from)
{
    if (!another || another->getCategory() != TileCategory::RoadCategory)
        return;

    BuildingTile *road_tile = static_cast<BuildingTile *>(another);
    if (road_tile->connectableFrom(from))
    {
        this->node_->connect(road_tile->getNode());
    }
}

void BuildingTile::rotate()
{
    dir_ = sf::Vector2f(dir_.y, -dir_.x);
    rect_.rotate(90);
 /*   if (light_)
        light_->initPos(pos_, dir_, size_);
*/
}

void BuildingTile::flip()
{
    rotate();
    rotate();
}

void BuildingTile::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(rect_, states);
 /*   if (light_)
        target.draw(*light_, states);
*/
}

} // namespace TrafficSim