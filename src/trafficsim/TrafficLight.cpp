#include "TrafficLight.hpp"

#include <iostream>

namespace TrafficSim
{

TrafficLight::TrafficLight(const RoadTile *tile, unsigned int handler_id)
    : handler_id_(handler_id), shape_(sf::Vector2f(50, 20))
{
    setColor(RED);
    if (tile->getDir().x == 1)
    {
        pos_ = tile->getPos() + sf::Vector2f(tile->getSize()-shape_.getSize().x, tile->getSize());
    }
    else if (tile->getDir().x == -1)
    {
        pos_ = tile->getPos() + sf::Vector2f(shape_.getSize().x, 0);
        shape_.rotate(180);
    }
    else if (tile->getDir().y == 1)
    {
        pos_ = tile->getPos() + sf::Vector2f(tile->getSize(), shape_.getSize().x);
        shape_.rotate(270);
    }
    else if (tile->getDir().y == -1)
    {
        pos_ = tile->getPos() + sf::Vector2f(0, tile->getSize() - shape_.getSize().x);
        shape_.rotate(90);
    }
    shape_.setPosition(pos_);
}

void TrafficLight::update(float delta_time)
{
    activated_for_ += delta_time;
    if(color_ == YELLOW && activated_for_ < green_time_ && activated_for_ > yellow_time_)
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
