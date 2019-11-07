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
    sf::Clock deltatime_;
    sf::Clock gametime_;
};
} // namespace TrafficSim
