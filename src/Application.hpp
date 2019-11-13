#pragma once

#include "Window.hpp"
#include "Map.hpp"

namespace TrafficSim
{
class Application
{
public:
    Application();
    void run();
    void close();

private:
    Window window_;
    Map map_;
    // This is resetted every frame. It tracks time between two frames
    sf::Clock deltatime_;
    // This timer will not be resetted. It will track time from start
    sf::Clock gametime_;
};
} // namespace TrafficSim
