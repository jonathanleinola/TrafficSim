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
    
    // gets called when app state is changed
    void setSimulating(bool val);

    //Entity handling
    void update(const sf::Time &game_time, float delta_time);

    // Add car to closest Road to "spawn_pos". It's destination will be 
    // closest Road to "dest"
    void addCar(const sf::Vector2f &spawn_pos, const sf::Vector2f &dest);

    // For trafficLight handlers
    void removeLight(TrafficLight *light);
    void addLight(TrafficLight *light, unsigned int handler_id = UINT_MAX);
    void newLightHandler(TrafficLight *light = nullptr);
    unsigned int getCurrentHandlerId() const { return current_handler_id_; }

    // Inherited from sf::Drawable base class, draws Grid, cars and Traffic Light connections if in editing mode
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    // Returns clocest Node to "pos" which is on the Road.
    std::shared_ptr<Node> closestRoadNode(const sf::Vector2f &pos);
    // Loops over cars_, and deletes all finished cars
    void removeFinishedCars();

public:
    Grid grid_;

private:
    bool simulating_ = false;
    std::vector<std::unique_ptr<Car>> cars_;
    std::vector<std::unique_ptr<TrafficLightHandler>> light_handlers_;
    unsigned int current_handler_id_ = 0;

};

} // namespace TrafficSim
