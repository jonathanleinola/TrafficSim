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

#include "DataHandler.hpp"
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
}

Application *Application::GetInstance()
{
    return AppInstance;
}

void Application::run()
{
    std::map<std::string, std::unique_ptr<sf::Texture>> textures;
    DataHandler::LoadTexturesFromFile("texture_list.txt", textures);

    StraightRoad::SetTexture(textures["straight_road"].get());
    RoadTurn::SetTextures(textures["right_turn"].get(), textures["left_turn"].get());
    RoadIntersection::SetTextures(textures["right_intersection"].get(), textures["left_intersection"].get());
    RoadTrisection::SetTextures(textures["right_trisection"].get(), textures["left_trisection"].get());
    RoadJunction::SetTextures(textures["right_junction"].get(), textures["left_junction"].get());

    // give random seed
    srand(time(NULL));

    float last_time = gametime_.getElapsedTime().asSeconds();

    //Main loop
    while (window_.isOpen())
    {
        if (last_time + 1.f < gametime_.getElapsedTime().asSeconds())
        {
            last_time = gametime_.getElapsedTime().asSeconds();
            map_.addCar(sf::Vector2f(rand() % window_.getWidth(), rand() % window_.getHeight()), sf::Vector2f(rand() % window_.getWidth(), rand() % window_.getHeight()), textures["blue_car"].get());
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
