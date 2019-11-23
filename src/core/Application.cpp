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
        if (last_time < time_line_.getRealTime() && time_line_.getMultiplier())
        {
            last_time = time_line_.getRealTime() + 2.f / time_line_.getMultiplier();
            map_.addCar(sf::Vector2f(rand() % window_.getWidth(), rand() % window_.getHeight()), sf::Vector2f(rand() % window_.getWidth(), rand() % window_.getHeight()));
        }

        window_.pollEvent();
        handleInputBuffers(time_line_.getFrameTime(), delta_mouse_pos - sf::Mouse::getPosition());
        map_.update(time_line_.getGameTime());
        time_line_.update();

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
