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
#include "RoadIntersection.hpp"
#include "RoadTrisection.hpp"

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
    sf::Texture carTexture;

    if (DataHandler::LoadTexture("yellow_car.jpeg", carTexture))
        return;

    sf::Texture roadTexture, rightTexture, leftTexture, rightIntersection, leftIntersection, rightTrisection, leftTrisection;

    if (DataHandler::LoadTexture("straight_road.png", roadTexture))
        return; // error, lets stop our program
    if (DataHandler::LoadTexture("right_turn.png", rightTexture))
        return;
    if (DataHandler::LoadTexture("left_turn.png", leftTexture))
        return;
    if (DataHandler::LoadTexture("right_intersection.png", rightIntersection))
        return;
    if (DataHandler::LoadTexture("left_intersection.png", leftIntersection))
        return;
    if (DataHandler::LoadTexture("right_trisection.png", rightTrisection))
        return;
    if (DataHandler::LoadTexture("left_trisection.png", leftTrisection))
        return;

    StraightRoad::SetTexture(&roadTexture);
    RoadTurn::SetTextures(&rightTexture, &leftTexture);
    RoadIntersection::SetTextures(&rightIntersection, &leftIntersection);
    RoadTrisection::SetTextures(&rightTrisection, &leftTrisection);

    // give random seed
    srand(time(NULL));

    float last_time = gametime_.getElapsedTime().asSeconds();

    //Main loop
    while (window_.isOpen())
    {
        if (last_time + 1.f < gametime_.getElapsedTime().asSeconds())
        {
            last_time = gametime_.getElapsedTime().asSeconds();
            map_.addCar(sf::Vector2f(rand() % window_.getWidth(), rand() % window_.getHeight()), sf::Vector2f(rand() % window_.getWidth(), rand() % window_.getHeight()), carTexture);
        }
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
