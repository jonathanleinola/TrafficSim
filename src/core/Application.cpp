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
#include "trafficsim/HomeRoad.hpp"

namespace TrafficSim
{

Application *Application::AppInstance = nullptr;

Application::Application()
    : builder_(map_, window_)
{
    AppInstance = this;
    data_.loadTexturesFromFile("texture_list.txt");
    StraightRoad::SetTexture(data_.getTextrue("straight_road"));
    HomeRoad::SetTexture(data_.getTextrue("home_road"));
    RoadTurn::SetTextures(data_.getTextrue("right_turn"), data_.getTextrue("left_turn"));
    RoadIntersection::SetTextures(data_.getTextrue("right_intersection"), data_.getTextrue("left_intersection"));
    RoadTrisection::SetTextures(data_.getTextrue("right_trisection"), data_.getTextrue("left_trisection"));
    RoadJunction::SetTextures(data_.getTextrue("right_junction"), data_.getTextrue("left_junction"));
    Car::AddTexture(data_.getTextrue("blue_car"));
    Car::AddTexture(data_.getTextrue("brown_car"));
    Car::AddTexture(data_.getTextrue("green_car"));
    Car::AddTexture(data_.getTextrue("grey_car"));
    Car::AddTexture(data_.getTextrue("white_car"));
    Car::AddTexture(data_.getTextrue("red_car"));
    Car::AddTexture(data_.getTextrue("teal_car"));
}

void Application::run()
{
    // give random seed
    srand(time(NULL));

    float last_time = time_line_.getRealTime();
    sf::Vector2i delta_mouse_pos = sf::Mouse::getPosition();

    //Main loop
    while (window_.isOpen())
    {
        if (last_time < time_line_.getRealTime() && time_line_.getMultiplier() && app_state_ != Editing)
        {
            last_time = time_line_.getRealTime() + 1.6f / time_line_.getMultiplier();
            map_.addCar(sf::Vector2f(rand() % window_.getWidth(), rand() % window_.getHeight()), sf::Vector2f(rand() % window_.getWidth(), rand() % window_.getHeight()));
        }

        window_.pollEvent();

        map_.update(time_line_.getGameTime(), time_line_.getFrameTime() * time_line_.getMultiplier());
        time_line_.update();

        handleInputBuffers(delta_mouse_pos - sf::Mouse::getPosition());
        delta_mouse_pos = sf::Mouse::getPosition();

        window_.clear();
        //Drawing happens between window.clear() and window.draw()
        window_.draw(map_);
        drawGUI();
        window_.display();
    }
}

void Application::changeState(State new_state)
{
    app_state_ = new_state;
    switch (app_state_)
    {
    case Editing:
        builder_.setBuildingMode(true);
        map_.setSimulating(false);
        break;
    case Simulating:
        builder_.setBuildingMode(false);
        map_.setSimulating(true);
        break;
    default:
        break;
    }
}

const char *state_mode(State state)
{
    return (const char *[]){
        "Editing",
        "Simulating"}[state];
}

void Application::drawGUI()
{
    if (app_state_ == Simulating)
        time_line_.drawGUI();
    if (app_state_ == Editing)
        builder_.drawGUI();

    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Load"))
            {
            }
            if (ImGui::MenuItem("Save"))
            {
                data_.saveMap("test", map_.grid_);
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Mode"))
        {
            for (int i = 0; i < State::StateCount; i++)
            {
                State new_state = static_cast<State>(i);
                if (ImGui::MenuItem(state_mode(new_state), "", app_state_ == new_state))
                    changeState(new_state);
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
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
    default:
        break;
    }
}

void Application::handleInputBuffers(const sf::Vector2i &delta_mp)
{
    // LEFT mouse button is pressed down
    if (button_buffer_[sf::Mouse::Left])
    {
        // if left control is down add a road if not move map
        if (key_buffer_[sf::Keyboard::LControl] && app_state_ == Editing)
            builder_.slideAdd(window_.convert(sf::Mouse::getPosition(window_.getWindow())));
        else
            window_.moveView(delta_mp);
    }
}

void Application::close()
{
}

Application *Application::GetInstance()
{
    return AppInstance;
}

} // namespace TrafficSim
