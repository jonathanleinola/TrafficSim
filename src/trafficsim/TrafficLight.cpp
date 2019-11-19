#include "TrafficLight.hpp"

#include <iostream>

namespace TrafficSim
{

TrafficLight::TrafficLight(const sf::Vector2f &pos, const sf::Vector2f &dir, float tile_size, unsigned int handler_id)
    : handler_id_(handler_id), shape_(sf::Vector2f(50, 20))
{
    setColor(RED);
    initPos(pos, dir, tile_size);
}

void TrafficLight::initPos(const sf::Vector2f &pos, const sf::Vector2f &dir, float tile_size)
{
    if (dir.x == 1)
    {
        pos_ = pos + sf::Vector2f(tile_size - shape_.getSize().x, tile_size - shape_.getSize().y);
        shape_.setRotation(0);
    }
    else if (dir.x == -1)
    {
        pos_ = pos + sf::Vector2f(shape_.getSize().x, shape_.getSize().y);
        shape_.setRotation(180);
    }
    else if (dir.y == 1)
    {
        pos_ = pos + sf::Vector2f(tile_size - shape_.getSize().y, shape_.getSize().x);
        shape_.setRotation(270);
    }
    else if (dir.y == -1)
    {
        pos_ = pos + sf::Vector2f(shape_.getSize().y, tile_size - shape_.getSize().x);
        shape_.setRotation(90);
    }
    shape_.setPosition(pos_);
}

void TrafficLight::update(float delta_time)
{
    activated_for_ += delta_time;
    if (color_ == YELLOW && activated_for_ < green_time_ && activated_for_ > yellow_time_)
        setColor(GREEN);
    // Yellow just before de activation
    if (color_ == GREEN && activated_for_ > green_time_ - yellow_time_)
    {
        setColor(YELLOW);
    }
    // Red
    else if (activated_for_ > green_time_)
    {
        deActivate();
    }
}

void TrafficLight::activate()
{
    activated_for_ = 0;
    activated_ = true;
    setColor(YELLOW);
}

void TrafficLight::deActivate()
{
    activated_ = false;
    setColor(RED);
}

void TrafficLight::setColor(LightColor color)
{
    color_ = color;
    switch (color_)
    {
    case RED:
        shape_.setFillColor(sf::Color(153, 0, 50));
        break;
    case YELLOW:
        shape_.setFillColor(sf::Color(234, 224, 25));
        break;
    case GREEN:
        shape_.setFillColor(sf::Color(52, 183, 40));
        break;
    }
}

void TrafficLight::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(shape_, states);
}

} // namespace TrafficSim
