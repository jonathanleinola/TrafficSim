#pragma once

#include <SFML/Graphics.hpp>

#include "core/Window.hpp"

namespace TrafficSim
{
class TimeLine
{
public:
    TimeLine();

    // Returns game time in seconds
    float getGameTime() const;
    // Returns time from starting the app in seconds
    float getRealTime() const;
    // Returns time elapsed from last frame
    float getFrameTime() const;
    // Returns multiplier which is used to speed up game time
    float getMultiplier() const { return multiplier_; }

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