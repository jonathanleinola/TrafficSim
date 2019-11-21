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

    unsigned int getLightCount() const { return lights_.size(); }

    void addLight(TrafficLight *light);
    void removeLight(void *light_to_remove, const sf::Vector2f &pos);

    void update(float delta_time);

    const std::vector<TrafficLight *> &getLights() const { return lights_; }

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    const unsigned int handler_id_;
    // index of active light
    unsigned int active_light_ = UINT_MAX;

    std::vector<TrafficLight *> lights_;

    // For drawing connections between lights
    std::vector<sf::Vertex> vertices_;
};

} // namespace TrafficSim
