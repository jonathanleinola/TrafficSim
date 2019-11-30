#include "BuildingHandler.hpp"
#include "Rando.hpp"

namespace TrafficSim
{

BuildingHandler::BuildingHandler(const BuildingTile *building_tile, const Tile *tile, unsigned int handler_id)
    : building_tile_(building_tile), closest_road_(tile), id_(handler_id)
{
    initDay();
}

void BuildingHandler::initDay()
{
    for (unsigned int i = 0; i < 17280; ++i)
    {
        leaving_times_.emplace_back(i * 5);
    }
}

bool BuildingHandler::update(const sf::Time &game_time)
{
    if (leaving_times_.front() <= game_time.asSeconds())
    {
        while(leaving_times_.front() <= game_time.asSeconds())
            leaving_times_.pop_front();
        return true;
    }
    return false;
}

void BuildingHandler::dispatchCar()
{
}

} // namespace TrafficSim