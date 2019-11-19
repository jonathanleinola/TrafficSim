#include "TrafficLightHandler.hpp"

namespace TrafficSim
{

TrafficLightHandler::TrafficLightHandler(unsigned int handler_id)
    : handler_id_(handler_id)
{
}

void TrafficLightHandler::addLight(TrafficLight *light)
{
    lights_.push_back(light);
    active_light_ = 0;
}

void TrafficLightHandler::removeLight(void *light_to_remove)
{
    lights_.erase(std::remove_if(lights_.begin(), lights_.end(), [&light_to_remove](const auto &light_element) -> bool {
                      return light_to_remove == light_element;
                  }),
                  lights_.end());
}

void TrafficLightHandler::update(float delta_time)
{
    // this means that there is no light added to this object
    if (lights_.size() < 1)
        return;
    if(active_light_ >= lights_.size())
        active_light_ = 0;
    lights_.at(active_light_)->update(delta_time);
    // While current light is active we can't change other lights
    if (lights_.at(active_light_)->isActivated())
        return;

    // Change active light
    if (active_light_ + 1 < lights_.size())
        active_light_++;
    else
        active_light_ = 0;

    lights_.at(active_light_)->activate();
}

void TrafficLightHandler::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
}

} // namespace TrafficSim
