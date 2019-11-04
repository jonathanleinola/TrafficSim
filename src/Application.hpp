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
};
} // namespace TrafficSim
