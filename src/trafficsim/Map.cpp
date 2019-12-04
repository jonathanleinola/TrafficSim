#include "Map.hpp"

#include <fstream>
#include <cfloat>   // FLT_MAX
#include <iostream> // FLT_MAX
#include <memory>

#include "Rando.hpp"
#include "RoadTile.hpp"

namespace TrafficSim
{

Map::Map()
    : grid_(120)
{
}

void Map::clearMap()
{
    cars_.clear();
    light_handlers_.clear();
    building_handlers_.clear();
    unsigned int current_handler_id_ = 0;
    unsigned int current_building_id_ = 0;
    grid_.init();
}

void Map::initDay()
{
    for(unsigned int i = 0; i < grid_.getTotalTileCount(); ++i)
    {
        if(grid_.getTile(i)->getCategory() == TileCategory::RoadCategory)
        {
            grid_.getTile(i)->getNode()->resetCounter();
        }
    }
    for (auto it = building_handlers_.begin(); it != building_handlers_.end(); ++it)
    {
        it->second->initDay();
    }
}

void Map::update(const sf::Time &game_time, float delta_time)
{
    // Move cars, and other things which are dependent on time
    //cars, humans, trafficlights
    if (!simulating_)
        return;

    for (auto ita = building_handlers_.begin(); ita != building_handlers_.end(); ++ita)
    {
        if (ita->second->update(game_time))
        {
            Rando r(building_handlers_.size());
            int index = r.uniroll() - 1;
            int i = 0;
            const Tile *dest_tile;
            for (auto itb = building_handlers_.begin(); itb != building_handlers_.end(); ++itb)
            {
                if (index == i)
                {
                    dest_tile = itb->second->getClosestRoad();
                    break;
                }
                i++;
            }
            auto spawn_tile = ita->second->getClosestRoad();
            if(dest_tile && spawn_tile)
                addCar(spawn_tile, dest_tile);
        }
    }

    for (auto &car : cars_)
        car->update(game_time, delta_time, cars_, light_handlers_);
    removeFinishedCars();

    for (auto ita = light_handlers_.begin(); ita != light_handlers_.end(); ++ita)
        ita->second->update(delta_time);
}

void Map::addCar(const Tile *spawn_pos, const Tile *dest)
{
    cars_.push_back(std::make_unique<Car>(Car(spawn_pos->getNode(), dest->getNode(), sf::Vector2f(50, 100))));
}

unsigned int Map::addBuilding(BuildingTile *building)
{
    auto closest_road_node = closestRoadNode(building->getCenter());
    if (closest_road_node)
        building_handlers_.insert({current_building_id_, std::make_unique<BuildingHandler>(building, grid_.getTile(closest_road_node->getPos()), current_building_id_)});
    else
        building_handlers_.insert({current_building_id_, std::make_unique<BuildingHandler>(building, nullptr, current_building_id_)});

    current_building_id_++;
    return current_building_id_ - 1;
}

void Map::updateClosestRoads()
{
    for (auto it = building_handlers_.begin(); it != building_handlers_.end(); ++it)
    {
        auto closest_road_node = closestRoadNode(it->second->getBuildingTile()->getCenter());
        if(closest_road_node)
            it->second->setClosestRoad(grid_.getTile(closest_road_node->getPos()));
    }
}

void Map::addLight(TrafficLight *light, unsigned int handler_id)
{
    if (light_handlers_.find(handler_id) == light_handlers_.end())
    {
        if (handler_id < UINT_MAX)
        {
            light_handlers_.insert({handler_id, std::make_unique<TrafficLightHandler>(handler_id)});
        }
        else
            light_handlers_.insert({0, std::make_unique<TrafficLightHandler>(0)});
    }

    if (light_handlers_.find(handler_id) != light_handlers_.end())
        light_handlers_.at(handler_id)->addLight(light);
    else
        light_handlers_.at(current_handler_id_)->addLight(light);
}

void Map::newLightHandler(TrafficLight *light)
{
    current_handler_id_++;
    light_handlers_.insert({current_handler_id_, std::make_unique<TrafficLightHandler>(current_handler_id_)});

    if (light)
    {
        light_handlers_.at(light->getHandlerId())->removeLight(light, light->getPos());
        light->setHandlerId(current_handler_id_);
        light_handlers_.at(current_handler_id_)->addLight(light);
    }
}

void Map::removeBuilding(unsigned int id)
{
    building_handlers_.erase(id);
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
        if (grid_.getTile(i)->getCategory() == TileCategory::RoadCategory)
        {
            auto road_tile = static_cast<RoadTile *>(grid_.getTile(i));
            if (road_tile->getType() == RoadType::StraightRoadType)
            {
                float dist = VectorMath::Distance(pos, grid_.getTile(i)->getCenter());
                if (closest_distance > dist)
                {
                    closest_distance = dist;
                    closest = grid_.getTile(i)->getNode();
                }
            }
        }
    }
    return closest;
}

void Map::setSimulating(bool val)
{
    if (simulating_ == val)
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
        for (auto ita = light_handlers_.begin(); ita != light_handlers_.end(); ++ita)
            target.draw(*ita->second, states);
    }
}
} // namespace TrafficSim