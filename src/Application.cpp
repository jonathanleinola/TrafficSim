#include "Application.hpp"

namespace TrafficSim
{

Application::Application()
{
}

void Application::run()
{
    //Main loop
    while (window_.isOpen())
    {
        window_.pollEvent();
        window_.clear();
        window_.display();
    }
}

void Application::close()
{

}

} // namespace TrafficSim
