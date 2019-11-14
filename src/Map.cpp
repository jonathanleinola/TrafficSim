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

void Map::loadMap(std::string path, int sizeX, int sizeY)
{
    std::fstream mapFile;
    mapFile.open(path);

    mapFile.close();
}

void Map::update(float delta_time)
{
    // Move cars, and other things which are dependent on time
    //cars, humans, trafficlights
    for (auto &car : cars_)
        car->update(delta_time, cars_);
    removeFinishedCars();
}

void Map::removeFinishedCars()
{
    cars_.erase(std::remove_if(cars_.begin(), cars_.end(), [](const auto &car) -> bool { return car->isFinished(); }), cars_.end());
}

void Map::addCar(const sf::Vector2f &spawn_pos, const sf::Vector2f &dest, const sf::Texture &carTexture)
{
    auto n1 = closestRoadNode(spawn_pos);
    auto n2 = closestRoadNode(dest);
    std::cout << n1 << std::endl;
    std::cout << n2 << std::endl;

    cars_.push_back(std::make_unique<Car>(Car(closestRoadNode(spawn_pos), closestRoadNode(dest), sf::Vector2f(50, 100), carTexture)));
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
}
}; // namespace TrafficSim