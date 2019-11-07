#include "Application.hpp"

#include <memory>
#include <iostream>
#include <stdlib.h>     // rand
#include <time.h>       //time


namespace TrafficSim
{

Application::Application()
{

}

void Application::run()
{
    srand(time(NULL));
    // Example how roads are created
    // First we have two nodes in different locations
    // origin (0, 0) is left top corner
    auto n1 = std::make_shared<Node>(sf::Vector2f(0, window_.getHeight() / 2));
    auto n2 = std::make_shared<Node>(sf::Vector2f(window_.getWidth(), window_.getHeight() / 2));

    auto n3 = std::make_shared<Node>(sf::Vector2f(window_.getWidth() / 2, 0));
    auto n4 = std::make_shared<Node>(sf::Vector2f(window_.getWidth()  / 2, window_.getHeight()));

    // We need to connect them
    n1->connect(n2);
    n3->connect(n4);

    // Needs to only give it beginning node
    map_.createRoads(n1);
    map_.createRoads(n3);

    // we need to check if two roads crosses each other, because it will recursively search to all nodes which it is connected to
    map_.checkIntersections();
    unsigned int counter = 0;


    //Main loop
    while (window_.isOpen())
    {
        map_.update(clock_.getElapsedTime().asSeconds());
        clock_.restart();
        window_.pollEvent();
        window_.clear();
        //Drawing happens between window.clear() and window.draw()
        if(rand() % 1000 == 1)
        {
            counter = 0;
            map_.addCar(sf::Vector2f(rand() % 4000, rand() % 2000), sf::Vector2f(rand() % 4000, rand() % 2000));
        }
        window_.draw(map_);
        window_.display();
        counter++;
    }
}

void Application::close()
{
}

} // namespace TrafficSim
