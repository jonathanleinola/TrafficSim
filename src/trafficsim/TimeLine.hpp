#pragma once

#include <SFML/Graphics.hpp>

#include "core/Window.hpp"

namespace TrafficSim
{
class TimeLine
{
public:
    TimeLine();

    // Returns time as seconds
    float getGameTime() const;
    float getRealTime() const;
    float getFrameTime() const;

    // Need to call this once every frame so our game_clock_ will be updated
    void update();
    // sets game_clock_ to 0
    void restart();

    void setMultiplier(float multiplier);

    void drawGUI();

private:
    sf::Clock real_clock_;
    sf::Clock frame_clock_;
    sf::Time game_time_;

    // game_clock_multiplies
    float multiplier_ = 1.f;

private:
    std::string timeToString() const;
};
} // namespace TrafficSim