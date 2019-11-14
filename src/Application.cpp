#include "Application.hpp"

#include <memory>
#include <iostream>
#include <stdlib.h> // rand
#include <time.h>   //time

#include "DataHandler.hpp"

#include "imgui.h"
#include "imgui-SFML.h"
#include "imgui_internal.h"

namespace TrafficSim
{

Application::Application()
{
}

void Application::run()
{
    sf::Texture roadTexture, carTexture;

    if (DataHandler::LoadTexture("road.png", roadTexture))
        return;
    if (DataHandler::LoadTexture("yellow_car.jpeg", carTexture))
        return; // error, lets stop our program

    roadTexture.setRepeated(true);

    // give random seed
    srand(time(NULL));
    // Example how roads are created
    // First we have two nodes in different locations
    // origin (0, 0) is left top corner
    auto n1 = std::make_shared<Node>(sf::Vector2f(0, window_.getHeight() / 2));
    auto n2 = std::make_shared<Node>(sf::Vector2f(window_.getWidth(), window_.getHeight() / 2));

    auto n3 = std::make_shared<Node>(sf::Vector2f(window_.getWidth() / 2, 0));
    auto n4 = std::make_shared<Node>(sf::Vector2f(window_.getWidth() / 2, window_.getHeight()));

    // We need to connect them
    n1->connect(n2);
    n3->connect(n4);

    // Needs to only give it beginning node
    map_.createRoads(n1, roadTexture);
    map_.createRoads(n3, roadTexture);

    // we need to check if two roads crosses each other, because it will recursively search to all nodes which it is connected to
    map_.checkIntersections();

    float last_time = gametime_.getElapsedTime().asSeconds();
    float fps_array[3];
    fps_array[0] = 0.1f;
    fps_array[1] = 0.8f;
    fps_array[2] = 0.3f;
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
        // test
        ImGui::Begin("New window");
        int x = ImGui::GetContentRegionAvail().x;
        int y = ImGui::GetContentRegionAvail().y;
        ImGui::PlotLines("", fps_array, 3, 0, NULL, 0, 1, ImVec2(x, y));
        ImGui::End();
        //Drawing happens between window.clear() and window.draw()
        window_.draw(map_);

        window_.display();
    }
}

void Application::close()
{
}

} // namespace TrafficSim
