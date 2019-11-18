#include "TrafficLightHandler.hpp"

namespace TrafficSim
{

TrafficLightHandler::TrafficLightHandler(unsigned int handler_id)
    : handler_id_(handler_id)
{
}

void TrafficLightHandler::addLight(const RoadTile *road_tile)
{
    lights_.push_back(std::make_unique<TrafficLight>(road_tile, handler_id_));
    active_light_ = 0;
}

void TrafficLightHandler::update(float delta_time)
{
    // this means that there is no light added to this object
    if(active_light_ == UINT_MAX)
        return;
    lights_.at(active_light_)->update(delta_time);
    // While current light is active we can't change other lights
    if(lights_.at(active_light_)->isActivated())
        return;
    
    // Change active light
    if(active_light_ + 1 < lights_.size())
        active_light_++;
    else
        active_light_ = 0;
    
    lights_.at(active_light_)->activate();

}

void TrafficLightHandler::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for(const auto &light : lights_)
        target.draw(*light, states);
}

} // namespace TraffiSim
