#include "Window.hpp"

#include "imgui.h"
#include "imgui-SFML.h"
#include "imgui_internal.h"

#include "Application.hpp"

namespace TrafficSim
{

Window::Window()
    : window_(sf::VideoMode(sf::VideoMode::getDesktopMode().width / 2, sf::VideoMode::getDesktopMode().height / 2), "Traffic Simulator")
{
    window_.setVerticalSyncEnabled(true);
    ImGui::SFML::Init(window_);
    window_.resetGLStates();
    ImGui::SFML::Update(window_, clock_.restart());
    ImGui::SFML::Render(window_);
    ImGui::GetFont()->Scale = 3.0f;
}

void Window::clear()
{
    ImGui::SFML::Update(window_, clock_.restart());
    window_.clear();
}

void Window::display()
{
    ImGui::SFML::Render(window_);
    window_.display();
}

void Window::pollEvent()
{
    auto app = Application::GetInstance();
    sf::Event ev;
    while (window_.pollEvent(ev))
    {
        ImGui::SFML::ProcessEvent(ev);
        if (ev.type == sf::Event::Closed)
            window_.close();
        app->handleEvent(ev);
    }
}

} // namespace TrafficSim
