#pragma once
#include <SFML/Graphics.hpp>

namespace TrafficSim
{
class Window
{
public:
    Window(int width, int height);
    int getWidth() const { return window_.getSize().x; }
    int getHeight() const { return window_.getSize().y; }
    bool isOpen() const { return window_.isOpen(); }
    void pollEvent();
    void draw(const sf::Drawable &obj) { window_.draw(obj); };
    void clear() { window_.clear(); };
    void display() { window_.display(); };

private:
    sf::RenderWindow window_;
};
} // namespace TrafficSim
