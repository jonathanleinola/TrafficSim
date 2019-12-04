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
#include "trafficsim/HomeBuilding.hpp"

namespace TrafficSim
{

Application *Application::AppInstance = nullptr;

Application::Application()
    : builder_(map_, window_), statistics_(map_, window_)
{
    AppInstance = this;
    data_.loadTexturesFromFile("texture_list.txt");
    StraightRoad::SetTexture(data_.getTexture("straight_road"));
    HomeRoad::SetTexture(data_.getTexture("home_road"));
    RoadTurn::SetTextures(data_.getTexture("right_turn"), data_.getTexture("left_turn"));
    RoadIntersection::SetTextures(data_.getTexture("right_intersection"), data_.getTexture("left_intersection"));
    RoadTrisection::SetTextures(data_.getTexture("right_trisection"), data_.getTexture("left_trisection"));
    RoadJunction::SetTextures(data_.getTexture("right_junction"), data_.getTexture("left_junction"));
    Car::AddTexture(data_.getTexture("blue_car"));
    Car::AddTexture(data_.getTexture("brown_car"));
    Car::AddTexture(data_.getTexture("green_car"));
    Car::AddTexture(data_.getTexture("grey_car"));
    Car::AddTexture(data_.getTexture("white_car"));
    Car::AddTexture(data_.getTexture("red_car"));
    Car::AddTexture(data_.getTexture("teal_car"));
    HomeBuilding::SetTexture(data_.getTexture("home_building"));
    OfficeBuilding::SetTexture(data_.getTexture("office_building"));
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
            //map_.addCar(sf::Vector2f(rand() % window_.getWidth(), rand() % window_.getHeight()), sf::Vector2f(rand() % window_.getWidth(), rand() % window_.getHeight()));
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
    {
        time_line_.drawGUI();
        statistics_.drawGUI();
    }
    if (app_state_ == Editing)
        builder_.drawGUI();

    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))

        {   

            static char buf[32];
            const char *c;
            std::string file_name;
            ImGui::InputText("Filename", buf, IM_ARRAYSIZE(buf));
            if (ImGui::MenuItem("Load", "Ctrl+O"))
            {
                // ".ts" for traffic sim :)
                
                file_name=buf + std::string(".csv");
                c = file_name.c_str();
                data_.loadMap(c, builder_, map_.grid_);
            }
            if (ImGui::MenuItem("Save", "Ctrl+S"))
            {
                // ".ts" for traffic sim :)
                file_name=buf + std::string(".csv");
                c = file_name.c_str();
                data_.saveMap(c, map_.grid_);
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
        if (ImGui::BeginMenu("Scale"))
        {
            if (ImGui::MenuItem("Scale: 100%", "Ctrl+1", ImGui::GetFont()->Scale == 1.f))
                ImGui::GetFont()->Scale = 1.f;
            if (ImGui::MenuItem("Scale: 125%", "Ctrl+2", ImGui::GetFont()->Scale == 1.25f))
                ImGui::GetFont()->Scale = 1.25f;
            if (ImGui::MenuItem("Scale: 150%", "Ctrl+3", ImGui::GetFont()->Scale == 1.5f))
                ImGui::GetFont()->Scale = 1.5f;
            if (ImGui::MenuItem("Scale: 200%", "Ctrl+4", ImGui::GetFont()->Scale == 2.f))
                ImGui::GetFont()->Scale = 2.f;
            if (ImGui::MenuItem("Scale: 250%", "Ctrl+5", ImGui::GetFont()->Scale == 2.5f))
                ImGui::GetFont()->Scale = 2.5f;
            if (ImGui::MenuItem("Scale: 300%", "Ctrl+6", ImGui::GetFont()->Scale == 3.f))
                ImGui::GetFont()->Scale = 3.f;
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

void Application::handleEvent(const sf::Event &ev)
{
    builder_.handleInput(ev);
    statistics_.handleInput(ev);
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
    // Shortcuts
    if (ev.type == sf::Event::KeyPressed)
    {
        if (ev.key.code == sf::Keyboard::Num1 && key_buffer_[sf::Keyboard::LControl])
            ImGui::GetFont()->Scale = 1.f;
        else if (ev.key.code == sf::Keyboard::Num2 && key_buffer_[sf::Keyboard::LControl])
            ImGui::GetFont()->Scale = 1.25f;
        else if (ev.key.code == sf::Keyboard::Num3 && key_buffer_[sf::Keyboard::LControl])
            ImGui::GetFont()->Scale = 1.5f;
        else if (ev.key.code == sf::Keyboard::Num4 && key_buffer_[sf::Keyboard::LControl])
            ImGui::GetFont()->Scale = 2.f;
        else if (ev.key.code == sf::Keyboard::Num5 && key_buffer_[sf::Keyboard::LControl])
            ImGui::GetFont()->Scale = 2.5f;
        else if (ev.key.code == sf::Keyboard::Num6 && key_buffer_[sf::Keyboard::LControl])
            ImGui::GetFont()->Scale = 3.f;

        else if (ev.key.code == sf::Keyboard::S && key_buffer_[sf::Keyboard::LControl])
            data_.saveMap("test.csv", map_.grid_);
        else if (ev.key.code == sf::Keyboard::O && key_buffer_[sf::Keyboard::LControl])
            data_.loadMap("test.csv", builder_, map_.grid_);

        else if (ev.key.code == sf::Keyboard::Up && key_buffer_[sf::Keyboard::LShift])
        {
            float zoom_vals[6] = {1.f, 1.25, 1.5f, 2.f, 2.5f, 3.f};
            if (window_.gui_zoom_index < 5)
            {
                window_.gui_zoom_index++;
                ImGui::GetFont()->Scale = zoom_vals[window_.gui_zoom_index];
            }
        }
        else if (ev.key.code == sf::Keyboard::Down && key_buffer_[sf::Keyboard::LShift])
        {
            float zoom_vals[6] = {1.f, 1.25, 1.5f, 2.f, 2.5f, 3.f};
            if (window_.gui_zoom_index > 0)
            {
                window_.gui_zoom_index--;
                ImGui::GetFont()->Scale = zoom_vals[window_.gui_zoom_index];
            }
        }
    }
}

void Application::handleInputBuffers(const sf::Vector2i &delta_mp)
{
    // LEFT mouse button is pressed down
    if (button_buffer_[sf::Mouse::Left])
    {
        // store temporarily selected "radio button" option such as "Add Road"

        // if left control is down add a road
        if (key_buffer_[sf::Keyboard::LControl] && app_state_ == Editing)
            builder_.slideAction(window_.convert(sf::Mouse::getPosition(window_.getWindow())), AddRoad);

        // if left shift is down remove road or building
        else if (key_buffer_[sf::Keyboard::LShift] && app_state_ == Editing)
            builder_.slideAction(window_.convert(sf::Mouse::getPosition(window_.getWindow())), Remove);

        // if no control or shift keys pressed move map
        else
        {
            window_.moveView(delta_mp);
        }
    }
}

void Application::close()
{
    ImGui::SFML::Shutdown();
}

Application *Application::GetInstance()
{
    return AppInstance;
}

} // namespace TrafficSim
