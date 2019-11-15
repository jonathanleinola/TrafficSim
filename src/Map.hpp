#pragma once

#include "Car.hpp"
#include "Grid.hpp"

namespace TrafficSim
{
// This class is abstraction on everything what happens in our simulation
// cars, roads, intersections, building etc are added to a Map
class Map : public sf::Drawable
{
public:
    Map();
    ~Map();

    //Entity handling
    void update(float delta_time);
    void addCar(const sf::Vector2f &spawn_pos, const sf::Vector2f &dest, const sf::Texture &carTexture);

    Grid &getGrid() { return grid_; }
    std::shared_ptr<Node> closestRoadNode(const sf::Vector2f &pos);
    // Data handling
    // TODO - take std::string always as const ref or even better const char *
    void loadMap(std::string path, int sizeX, int sizeY);
    //Finds closest lane-node from map. If fromBegin is true -> finds beginning node else finds ending node
    // if there is two roads crossing each other we need to create intersection

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    std::vector<std::unique_ptr<Car>> cars_;
    Grid grid_;

    // Loops over cars_, and deletes all finished cars
    void removeFinishedCars();
};

} // namespace TrafficSim
