#include "Application.hpp"

#include <memory>
#include <iostream>

namespace TrafficSim
{

Application::Application()
{
}

void Application::run()
{
    // Example how roads are created
    // First we have two nodes in different locations
    // origin (0, 0) is left top corner
    auto n1 = std::make_shared<Node>(sf::Vector2f(window_.getWidth() / 4, window_.getHeight() / 2));
    auto n2 = std::make_shared<Node>(sf::Vector2f(window_.getWidth() * 3 / 4, window_.getHeight() / 2));

    // We need to connect them
    n1->connect(n2);

    // Needs to only give it beginning node
    map_.createRoads(n1);

    // we need to check if two roads crosses each other
    map_.checkIntersections();

    //Main loop
    while (window_.isOpen())
    {
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
