#include "Application.hpp"

#include <memory>
#include <iostream>
#include <string>
#include <utility>
#include <stdlib.h> // rand
#include <time.h>   //time

#include "imgui.h"
#include "imgui-SFML.h"
#include "imgui_internal.h"

#include "RoadTile.hpp"
#include "StraightRoad.hpp"
#include "RoadIntersection.hpp"
#include "RoadTrisection.hpp"
#include "RoadJunction.hpp"

namespace TrafficSim
{

Application *Application::AppInstance = nullptr;

Application::Application()
    : builder_(map_.getGrid())
{
    AppInstance = this;
    data_.loadTexturesFromFile("texture_list.txt");
    StraightRoad::SetTexture(data_.getTextrue("straight_road"));
    RoadTurn::SetTextures(data_.getTextrue("right_turn"), data_.getTextrue("left_turn"));
    RoadIntersection::SetTextures(data_.getTextrue("right_intersection"), data_.getTextrue("left_intersection"));
    RoadTrisection::SetTextures(data_.getTextrue("right_trisection"), data_.getTextrue("left_trisection"));
    RoadJunction::SetTextures(data_.getTextrue("right_junction"), data_.getTextrue("left_junction"));
}

void Application::run()
{
    // give random seed
    srand(time(NULL));

    float last_time = gametime_.getElapsedTime().asSeconds();

    //Main loop
    while (window_.isOpen())
    {
        if (last_time + 1.f < gametime_.getElapsedTime().asSeconds())
        {
            last_time = gametime_.getElapsedTime().asSeconds();
            map_.addCar(sf::Vector2f(rand() % window_.getWidth(), rand() % window_.getHeight()), sf::Vector2f(rand() % window_.getWidth(), rand() % window_.getHeight()), data_.getTextrue("blue_car"));
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

Application *Application::GetInstance()
{
    return AppInstance;
}

} // namespace TrafficSim
