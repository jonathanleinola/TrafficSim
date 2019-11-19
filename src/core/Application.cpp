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

#include "trafficsim/RoadTile.hpp"
#include "trafficsim/StraightRoad.hpp"
#include "trafficsim/RoadIntersection.hpp"
#include "trafficsim/RoadTrisection.hpp"
#include "trafficsim/RoadJunction.hpp"

namespace TrafficSim
{

Application *Application::AppInstance = nullptr;

Application::Application()
    : builder_(map_, window_)
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
    sf::Vector2i delta_mouse_pos = sf::Mouse::getPosition();

    //Main loop
    while (window_.isOpen())
    {
        if (last_time + 2.f < gametime_.getElapsedTime().asSeconds())
        {
            last_time = gametime_.getElapsedTime().asSeconds();
            map_.addCar(sf::Vector2f(rand() % window_.getWidth(), rand() % window_.getHeight()), sf::Vector2f(rand() % window_.getWidth(), rand() % window_.getHeight()), data_.getTextrue("blue_car"));
        }

        window_.pollEvent();
        map_.update(deltatime_.getElapsedTime().asSeconds());
        handleInputBuffers(deltatime_.getElapsedTime().asSeconds(), delta_mouse_pos - sf::Mouse::getPosition());
        deltatime_.restart();
        delta_mouse_pos = sf::Mouse::getPosition();

        window_.clear();
        //Drawing happens between window.clear() and window.draw()
        window_.draw(map_);
        builder_.drawGUI();
        window_.drawGUI();
        window_.display();
    }
}

void Application::handleEvent(const sf::Event &ev)
{
    builder_.handleInput(ev);
    switch (ev.type)
    {
    case sf::Event::KeyPressed:
        key_buffer_[ev.key.code] = true;
        break;
    case sf::Event::KeyReleased:
        key_buffer_[ev.key.code] = false;
        break;
    case sf::Event::MouseButtonPressed:
        button_buffer_[ev.mouseButton.button] = true;
        break;
    case sf::Event::MouseButtonReleased:
        button_buffer_[ev.mouseButton.button] = false;
        break;
    case sf::Event::MouseWheelScrolled:
        break;
    default:
        break;
    }
}

void Application::handleInputBuffers(const float deltatime, const sf::Vector2i &delta_mp)
{
    //Mouse buttons
    if (button_buffer_[sf::Mouse::Left])
        window_.moveView(delta_mp);
}

void Application::close()
{
}

Application *Application::GetInstance()
{
    return AppInstance;
}

} // namespace TrafficSim
