#pragma once

#include "Window.hpp"
#include "Map.hpp"
#include "MapBuilder.hpp"
#include "DataHandler.hpp"


namespace TrafficSim
{
class Application
{
public:
    Application();
    void run();
    void close();
    void handleEvent(const sf::Event &ev);

private:
    Window window_;
    Map map_;
    MapBuilder builder_;
    DataHandler data_;
    // This is resetted every frame. It tracks time between two frames
    sf::Clock deltatime_;
    // This timer will not be resetted. It will track time from start
    sf::Clock gametime_;

    static Application *AppInstance;

public:
    static Application *GetInstance();
};
} // namespace TrafficSim
