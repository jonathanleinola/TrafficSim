#include "Application.hpp"

#include <memory>
#include <iostream>
#include <stdlib.h> // rand
#include <time.h>   //time

namespace TrafficSim
{

Application::Application()
{
}

void Application::run()
{
    sf::Texture roadTexture;
    if (!roadTexture.loadFromFile("road.png"))
    {
        std::cout << "Could not load texture: " << "road.png" << std::endl;
        return;
    }
    else
    {
        std::cout << "Texture loaded." << std::endl;
        roadTexture.setRepeated(true);
    }
    
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
    //Main loop
    while (window_.isOpen())
    {
        if (last_time + 1.f < gametime_.getElapsedTime().asSeconds())
        {
            last_time = gametime_.getElapsedTime().asSeconds();
            map_.addCar(sf::Vector2f(rand() % window_.getWidth(), rand() % window_.getHeight()), sf::Vector2f(rand() % window_.getWidth(), rand() % window_.getHeight()));
        }
        map_.update(deltatime_.getElapsedTime().asSeconds());
        deltatime_.restart();

        window_.pollEvent();

        window_.clear();
        //Drawing happens between window.clear() and window.draw()
        window_.draw(map_);

        window_.display();
    }
}

void Application::close()
{
}

} // namespace TrafficSim
