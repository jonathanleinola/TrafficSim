#include "Window.hpp"

namespace TrafficSim
{

Window::Window(int width, int height)
    : window_(sf::VideoMode(width, height), "Traffic Simulator")
{
}

void Window::pollEvent()
{
    sf::Event Event;
    while (window_.pollEvent(Event))
    {
        if (Event.type == sf::Event::Closed)
            window_.close();
    }
}



} // namespace TrafficSim
