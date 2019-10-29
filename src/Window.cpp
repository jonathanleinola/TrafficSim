#include "Window.hpp"

namespace TrafficSim
{

Window::Window()
    : window_(sf::VideoMode(sf::VideoMode::getDesktopMode().width / 2, sf::VideoMode::getDesktopMode().height / 2), "Traffic Simulator")
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
