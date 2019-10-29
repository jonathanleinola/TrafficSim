#pragma once

#include "Window.hpp"

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
};
} // namespace TrafficSim
