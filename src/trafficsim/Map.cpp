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

void Map::update(const sf::Time &game_time, float delta_time)
{
    // Move cars, and other things which are dependent on time
    //cars, humans, trafficlights
    if(!simulating_)
        return;

    for (auto &car : cars_)
        car->update(game_time, delta_time, cars_, light_handlers_);
    removeFinishedCars();

    for (auto &light_handler : light_handlers_)
        light_handler->update(delta_time);
}

void Map::addCar(const sf::Vector2f &spawn_pos, const sf::Vector2f &dest)
{
    auto n1 = closestRoadNode(spawn_pos);
    auto n2 = closestRoadNode(dest);
    if (!n1)
        return;
    if (n1->getPos() == n2->getPos())
        return;
    cars_.push_back(std::make_unique<Car>(Car(closestRoadNode(spawn_pos), closestRoadNode(dest), sf::Vector2f(50, 100))));
}

void Map::addLight(TrafficLight *light, unsigned int handler_id)
{
    if (light_handlers_.size() < 1)
        light_handlers_.push_back(std::make_unique<TrafficLightHandler>(0));

    if (handler_id < light_handlers_.size())
        light_handlers_.at(handler_id)->addLight(light);
    else
        light_handlers_.at(current_handler_id_)->addLight(light);
}

void Map::newLightHandler(TrafficLight *light)
{
    if (light_handlers_.at(light_handlers_.size() - 1)->getLightCount() < 1)
    {
        current_handler_id_ = light_handlers_.size() - 1;
    }
    else
    {
        light_handlers_.push_back(std::make_unique<TrafficLightHandler>(light_handlers_.size()));
        current_handler_id_ = light_handlers_.size() - 1;
    }
    light_handlers_.at(light->getHandlerId())->removeLight(light, light->getPos());
    light->setHandlerId(current_handler_id_);
    light_handlers_.at(current_handler_id_)->addLight(light);
}

void Map::removeLight(TrafficLight *light)
{
    light_handlers_.at(light->getHandlerId())->removeLight(light, light->getPos());
}

void Map::removeFinishedCars()
{
    cars_.erase(std::remove_if(cars_.begin(), cars_.end(), [](const auto &car) -> bool { return car->isFinished(); }), cars_.end());
}

std::shared_ptr<Node> Map::closestRoadNode(const sf::Vector2f &pos)
{
    std::shared_ptr<Node> closest = nullptr;
    float closest_distance = FLT_MAX;
    for (unsigned int i = 0; i < grid_.getTotalTileCount(); ++i)
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

void Map::setSimulating(bool val)
{
    if(simulating_ == val)
        return;
    simulating_ = val;
    cars_.clear();
}

void Map::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(grid_, states);
    if (simulating_)
    {
        for (const auto &car : cars_)
            target.draw(*car, states);
    }
    else
    {
        for (auto &light_handler : light_handlers_)
            target.draw(*light_handler, states);
    }
}
} // namespace TrafficSim