#include "Application.hpp"

#include <memory>
#include <iostream>
#include <stdlib.h> // rand
#include <time.h>   //time

#include "imgui.h"
#include "imgui-SFML.h"
#include "imgui_internal.h"

#include "DataHandler.hpp"
#include "RoadTile.hpp"
#include "StraightRoad.hpp"

namespace TrafficSim
{

Application *Application::AppInstance = nullptr;

Application::Application()
    : builder_(map_.getGrid())
{
    AppInstance = this;
}

Application *Application::GetInstance()
{
    return AppInstance;
}

void Application::run()
{
    sf::Texture roadTexture, carTexture, rightTexture, leftTexture;

    if (DataHandler::LoadTexture("straight_road.png", roadTexture))
        return; // error, lets stop our program
    if (DataHandler::LoadTexture("yellow_car.jpeg", carTexture))
        return;
    if (DataHandler::LoadTexture("road_right_turn.png", rightTexture))
        return;
    if (DataHandler::LoadTexture("road_left_turn.png", leftTexture))
        return;

    StraightRoad::SetTexture(roadTexture);
    RoadTurn::SetTextures(rightTexture, leftTexture);
    // give random seed
    srand(time(NULL));

    float last_time = gametime_.getElapsedTime().asSeconds();

    //Main loop
    while (window_.isOpen())
    {
        map_.update(deltatime_.getElapsedTime().asSeconds());
        deltatime_.restart();

        window_.pollEvent();

        window_.clear();
        //Drawing happens between window.clear() and window.draw()
        window_.draw(map_);
        builder_.drawGUI();
        window_.display();
    }
}

void Application::handleEvent(const sf::Event &ev)
{
    builder_.handleInput(ev);
}

void Application::close()
{
}

} // namespace TrafficSim
