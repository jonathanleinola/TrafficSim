#pragma once

#include "Window.hpp"
#include "trafficsim/Map.hpp"
#include "trafficsim/MapBuilder.hpp"
#include "trafficsim/TimeLine.hpp"
#include "util/DataHandler.hpp"

namespace TrafficSim
{
class Application
{
public:
    Application();

    void run();
    void close();
    void handleEvent(const sf::Event &ev);
    void handleInputBuffers(const float deltatime, const sf::Vector2i &delta_mp);

private:
    Window window_;
    Map map_;
    MapBuilder builder_;
    TimeLine time_line_;
    DataHandler data_;

    // Input buffers
    bool key_buffer_[sf::Keyboard::KeyCount]{false};
    bool button_buffer_[sf::Mouse::ButtonCount]{false};

    static Application *AppInstance;

public:
    static Application *GetInstance();
};
} // namespace TrafficSim
