#include "TimeLine.hpp"

#include <iostream>
#include <string>

#include "imgui.h"
#include "imgui-SFML.h"
#include "imgui_internal.h"

namespace TrafficSim
{

TimeLine::TimeLine()
{
}

float TimeLine::getGameTime() const
{
    return game_time_.asSeconds();
}

float TimeLine::getRealTime() const
{
    return real_clock_.getElapsedTime().asSeconds();
}

float TimeLine::getFrameTime() const
{
    return frame_clock_.getElapsedTime().asSeconds();
}

void TimeLine::update()
{
    game_time_ += frame_clock_.getElapsedTime() * multiplier_;
    if (game_time_.asSeconds() > 86400)
        restart();
    frame_clock_.restart();
}

void TimeLine::restart()
{
    game_time_ = sf::seconds(0.f);
}

void TimeLine::setMultiplier(float multiplier)
{
    multiplier_ = multiplier;
}

std::string TimeLine::timeToString() const
{
    int houres = (int)(game_time_.asSeconds() / 60 / 60) % 60;
    int minutes = (int)(game_time_.asSeconds() / 60) % 60;
    int seconds = (int)game_time_.asSeconds() % 60;
    return  std::to_string(houres) + ":" + std::to_string(minutes) + ":" + std::to_string(seconds);
}

void TimeLine::drawGUI()
{
    float hours = game_time_.asSeconds() / 60 / 60;

    ImGui::Begin("Time");
    
    ImGui::Text(timeToString().c_str());

    ImGui::SliderFloat("Time scale", &multiplier_, 0.f, 20.f, "%.1f");
    ImGui::SliderFloat("Time", &hours, 0.f, 24.0f, "%.1f");

    game_time_ = sf::seconds(hours * 60 * 60);
    ImGui::End();
}

} // namespace TrafficSim