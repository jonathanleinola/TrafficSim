#include "Map.hpp"
#include <fstream>

namespace TrafficSim
{

Map::Map()
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
        car.update(delta_time);
}

void Map::checkIntersections()
{
    // keeps track of created intersections... We only need 1 intesection per 1 road crossing
    std::map<std::pair<int, int>, bool> created;
    for (unsigned int i = 0; i < roads_.size(); ++i)
    {
        auto r1 = roads_[i]->getEndPoints();
        for (unsigned int j = 0; j < roads_.size(); ++j)
        {
            // If we have already created intersection from i and j. j and i will be same so no need to make duplicate intersection
            if (i == j || created[{i, j}] || created[{j, i}])
                continue;
            auto r2 = roads_[j]->getEndPoints();
            auto t = VectorMath::IntersectionPoint(r1.first, r1.second, r2.first, r2.second);
            if (t > 0 && t < 1)
            {
                created[{i, j}] = true;
                intersections_.emplace_back(roads_[i], roads_[j], VectorMath::Lerp(r1.first, r1.second, t));
            }
        }
    }
}

void Map::constructRoad(const std::shared_ptr<Node> &cur, const std::shared_ptr<Road> &prevRoad, std::map<std::shared_ptr<Node>, bool> &visited)
{
    if (visited[cur])
        return;
    visited[cur] = true;
    for (const auto &neighbor : cur->getNeighbors())
    {
        if (prevRoad == nullptr)
            roads_.push_back(std::make_shared<Road>(cur, neighbor, 100.f));
        else
            roads_.push_back(std::make_shared<Road>(*prevRoad, neighbor));

        constructRoad(neighbor, roads_[roads_.size() - 1], visited);
    }
}

void Map::createRoads(const std::shared_ptr<Node> &begin)
{
    Road *road = nullptr;
    std::shared_ptr<Node> cur = begin;
    std::shared_ptr<Node> prev = nullptr;
    std::map<std::shared_ptr<Node>, bool> visited;
    constructRoad(cur, nullptr, visited);
}

void Map::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (const auto &road : roads_)
        target.draw(*road, states);
    for (const auto &intersection : intersections_)
        target.draw(intersection, states);
    for (const auto &car : cars_)
        target.draw(car, states);
}
}; // namespace TrafficSim