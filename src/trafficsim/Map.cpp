#include "Map.hpp"

#include <fstream>
#include <cfloat>   // FLT_MAX
#include <iostream> // FLT_MAX
#include <memory>

#include "RoadTile.hpp"

namespace TrafficSim
{

Map::Map()
    : grid_(120)
{
}

Map::~Map()
{
}

void Map::update(float delta_time)
{
    // Move cars, and other things which are dependent on time
    //cars, humans, trafficlights
    for (auto &car : cars_)
        car->update(delta_time, cars_, light_handlers_);
    removeFinishedCars();

    for (auto &light_handler : light_handlers_)
        light_handler->update(delta_time);
}

void Map::addCar(const sf::Vector2f &spawn_pos, const sf::Vector2f &dest, const sf::Texture *carTexture)
{
    auto n1 = closestRoadNode(spawn_pos);
    auto n2 = closestRoadNode(dest);
    if (!n1)
        return;
    if (n1->getPos() == n2->getPos())
        return;
    cars_.push_back(std::make_unique<Car>(Car(closestRoadNode(spawn_pos), closestRoadNode(dest), sf::Vector2f(50, 100), carTexture)));
}

void Map::addLight(RoadTile *road)
{
    if(light_handlers_.size() < 1)
        light_handlers_.push_back(std::make_unique<TrafficLightHandler>(0));
    if(road->getLight())
        return;
    road->addLight(0);
    light_handlers_.at(0)->addLight(road->getLight());
}

void Map::removeLight(RoadTile *road)
{
    void *light = road->getLight();
    if(!light)
        return;
    light_handlers_.at(road->removeLight())->removeLight(light);

}


void Map::removeFinishedCars()
{
    cars_.erase(std::remove_if(cars_.begin(), cars_.end(), [](const auto &car) -> bool { return car->isFinished(); }), cars_.end());
}

std::shared_ptr<Node> Map::closestRoadNode(const sf::Vector2f &pos)
{
    std::shared_ptr<Node> closest = nullptr;
    float closest_distance = FLT_MAX;
    for (unsigned int i = 0; i < grid_.getSize(); ++i)
    {
        if (grid_.getTile(i)->getType() == TileType::StraightRoadType)
        {
            float dist = VectorMath::Distance(pos, grid_.getTile(i)->getCenter());
            if (closest_distance > dist)
            {
                closest_distance = dist;
                closest = grid_.getTile(i)->getNode();
            }
        }
    }
    return closest;
}

void Map::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(grid_, states);
    for (const auto &car : cars_)
        target.draw(*car, states);
    for (auto &light_handler : light_handlers_)
        target.draw(*light_handler, states);
}
}; // namespace TrafficSim