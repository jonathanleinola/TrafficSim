#pragma once
#include <SFML/Graphics.hpp>

namespace TrafficSim
{
class Window
{
public:
    Window();

    //Getters
    int getWidth() const { return window_.getSize().x; }
    int getHeight() const { return window_.getSize().y; }
    bool isOpen() const { return window_.isOpen(); }

    void pollEvent();

    // For rendering stuff on the screen
    void draw(const sf::Drawable &obj) { window_.draw(obj); };
    void clear();
    void display();

private:
    sf::RenderWindow window_;
    sf::Clock clock_;
};
} // namespace TrafficSim
