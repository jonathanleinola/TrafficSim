#include "Window.hpp"

#include "imgui.h"
#include "imgui-SFML.h"
#include "imgui_internal.h"

#include "Application.hpp"

namespace TrafficSim
{

Window::Window()
    : window_(sf::VideoMode(sf::VideoMode::getDesktopMode().width / 2, sf::VideoMode::getDesktopMode().height / 2), "Traffic Simulator", sf::Style::Default, sf::ContextSettings(0, 0, 8)),
      view_(sf::View(sf::FloatRect(0, 0, sf::VideoMode::getDesktopMode().width / 2, sf::VideoMode::getDesktopMode().height / 2)))
{
    window_.setView(view_);
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
        else if (ev.type == sf::Event::MouseWheelScrolled)
        {
            zoomView(sf::Vector2i(ev.mouseWheelScroll.x, ev.mouseWheelScroll.y), ev.mouseWheelScroll.delta);
        }
        app->handleEvent(ev);
    }
}

void Window::moveView(const sf::Vector2i &delta_pos)
{
    view_.move(delta_pos.x * zoom_, delta_pos.y * zoom_);
    window_.setView(view_);
}

void Window::drawGUI()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Load"))
            {
            }
            if (ImGui::MenuItem("Save"))
            {
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

void Window::zoomView(sf::Vector2i relative_to, float zoom_dir)
{
    if (zoom_dir == 0)
        return;
    const sf::Vector2f beforeCoord{window_.mapPixelToCoords(relative_to)};
    const float zoomfactor = 1.1f;
    zoom_ = zoom_ * (zoom_dir < 0 ? zoomfactor : 1.f / zoomfactor);
    view_.setSize(window_.getSize().x * zoom_, window_.getSize().y * zoom_);
    window_.setView(view_);
    const sf::Vector2f afterCoord{window_.mapPixelToCoords(relative_to)};
    const sf::Vector2f offsetCoords{beforeCoord - afterCoord};
    view_.move(offsetCoords);
    window_.setView(view_);
}

} // namespace TrafficSim