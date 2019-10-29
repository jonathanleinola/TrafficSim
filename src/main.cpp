#include <iostream>
#include <vector>

#include "Window.hpp"

int main()
{
    TrafficSim::Window window(1280, 720);
    sf::RectangleShape rect(sf::Vector2f(10, 10));
    while (window.isOpen())
    {
        window.pollEvent();
        window.clear();
        window.draw(rect);
        window.display();
    }
}