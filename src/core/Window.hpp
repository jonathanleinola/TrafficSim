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

    // View stuff
    sf::Vector2i convert(const sf::Vector2f &point) const { return window_.mapCoordsToPixel(point); }
    sf::Vector2f convert(const sf::Vector2i &point) const { return window_.mapPixelToCoords(point); }
    void moveView(const sf::Vector2i &delta_pos);

    void pollEvent();
    void drawGUI();

    // For rendering stuff on the screen
    void draw(const sf::Drawable &obj) { window_.draw(obj); };
    void clear();
    void display();

private:
    void zoomView(sf::Vector2i relative_to, float zoom);


private:
    sf::RenderWindow window_;
    sf::Clock clock_;
    sf::View view_;
    float zoom_ = 1.f;
};
} // namespace TrafficSim