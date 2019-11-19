#pragma once

#include <vector>
#include <memory> // std::unique_ptr
#include <climits>

#include "TrafficLight.hpp"

namespace TrafficSim
{

class TrafficLightHandler : public sf::Drawable
{
public:
    TrafficLightHandler(unsigned int handler_id);

    void addLight(TrafficLight *light);
    void removeLight(void *light_to_remove);

    void update(float delta_time);

    const std::vector<TrafficLight *> &getLights() const { return lights_; }

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    const unsigned int handler_id_;
    // index of active light
    unsigned int active_light_ = UINT_MAX;

    // TODO ? Lights that are stored in the same inner vector can be activated (green) at the same time
    std::vector<TrafficLight *> lights_;
};

} // namespace TrafficSim
