#include "Car.hpp"

#include <iostream>

namespace TrafficSim
{

Car::Car(const std::shared_ptr<Node> &pos, const std::shared_ptr<Node> &dest, const sf::Vector2f &size)
    : pos_(pos), dest_(dest), prev_(pos), shape_(size), speed_(200)
{
    shape_.setOrigin({shape_.getSize().x / 2, shape_.getSize().y / 2});
    shape_.setPosition(pos_->getPos());
    shape_.setFillColor(sf::Color::Green);
    findRoute();
    for(const auto& node : route_)
        std::cout << node << std::endl;
}
void Car::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(shape_, states);
}

void Car::update(float deltatime)
{
    if (route_.size() < 1)
        return;

    if (VectorMath::Distance(shape_.getPosition(), route_.front()->getPos()) < 5.f)
    {
        shape_.setPosition(route_.front()->getPos());
        prev_ = std::make_shared<Node>(*route_.front());
        route_.pop_front();
        // Don't go back to beginning node
        if(route_.front() == pos_)
            route_.pop_front();

        if(route_.size() < 1)
            return;
    }

    sf::Vector2f dir = VectorMath::Normalize(route_.front()->getPos() - prev_->getPos());
    shape_.setRotation(VectorMath::Angle(dir, {0, 1.f}) * 180.f / M_PI);

    shape_.move(dir * deltatime * speed_);
}

void Car::findRoute()
{
    std::map<std::shared_ptr<Node>, bool> visited;
    pos_->search_DFS(pos_, dest_, visited, route_);
}
} // namespace TrafficSim
