#pragma once

#include "Intersection.hpp"
#include "Car.hpp"

namespace TrafficSim
{
// This class is abstractio on everything what happens in our simulation
// cars, roads, intersections, building etc are added to a Map
class Map : public sf::Drawable
{
public:
    Map();
    ~Map();

    //Entity handling
    void loadMap(std::string path, int sizeX, int sizeY);
    void update(float delta_time);
    void createRoads(const std::shared_ptr<Node> &begin);
    void addCar(const std::shared_ptr<Node> &pos);
    void checkIntersections();

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    std::vector<std::shared_ptr<Road>> roads_;
    std::vector<Car> cars_;
    std::vector<Intersection> intersections_;

    // Constructs roads from nodes using recursive DFS algorithm to iterate over node graph
    void constructRoad(const std::shared_ptr<Node> &cur, const std::shared_ptr<Road> &prevRoad, std::map<std::shared_ptr<Node>, bool> &visited);
};

} // namespace TrafficSim
