#pragma once

#include "Intersection.hpp"
#include "Car.hpp"
#include "Tile.hpp"

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
    void update(float delta_time);
    void addCar(const sf::Vector2f &spawn_pos, const sf::Vector2f &dest);
    void createRoads(const std::shared_ptr<Node> &begin, const sf::Texture &texture);

    // Data handling
    // TODO - take std::string always as const ref or even better const char *
    void loadMap(std::string path, int sizeX, int sizeY);
    void createGrid(int window_width, int window_height);

    //Finds closest lane-node from map. If fromBegin is true -> finds beginning node else finds ending node
    std::shared_ptr<Node> closestRoadNode(const sf::Vector2f &pos, bool fromBegin);
    // if there is two roads crossing each other we need to create intersection
    void checkIntersections();

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    std::vector<Road> roads_;
    std::vector<std::unique_ptr<Car>> cars_;
    std::vector<Intersection> intersections_;
    std::vector<std::shared_ptr<Tile>> grid_;

    // Constructs roads from nodes using recursive DFS algorithm to iterate over node graph
    void constructRoad(const std::shared_ptr<Node> &cur, const Road *prevRoad, std::map<std::shared_ptr<Node>, bool> &visited, const sf::Texture &texture);
    // Loops over cars_, and deletes all finished cars
    void removeFinishedCars();
};

} // namespace TrafficSim
