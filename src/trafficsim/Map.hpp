#pragma once

#include <climits> // UINT_MAX

#include "Car.hpp"
#include "Grid.hpp"
#include "RoadTile.hpp"
#include "TrafficLightHandler.hpp"

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

    void addCar(const sf::Vector2f &spawn_pos, const sf::Vector2f &dest, const sf::Texture *carTexture);
    
    void removeLight(TrafficLight *light);
    void addLight(TrafficLight *light);
    void newLightHandler(TrafficLight *light);

    unsigned int getCurrentHandlerId() const { return current_handler_id_; }

    Grid &getGrid() { return grid_; }
    std::shared_ptr<Node> closestRoadNode(const sf::Vector2f &pos);

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    std::vector<std::unique_ptr<Car>> cars_;
    Grid grid_;
    std::vector<std::unique_ptr<TrafficLightHandler>> light_handlers_;
    unsigned int current_handler_id_ = 0;

private:
    // Loops over cars_, and deletes all finished cars
    void removeFinishedCars();
};

} // namespace TrafficSim
