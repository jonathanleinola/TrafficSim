#include "Car.hpp"

#include <iostream>
#include <algorithm> // std::max

namespace TrafficSim
{

Car::Car(const std::shared_ptr<Node> &pos, const std::shared_ptr<Node> &dest, const sf::Vector2f &size, const sf::Texture &carTexture)
    : pos_(pos), dest_(dest), prev_(pos), shape_(size), speed_(200), acceleration_(0)
{
    shape_.setFillColor(sf::Color(50,0,0,50));
    shape_.setTexture(&carTexture);
    shape_.setOrigin({shape_.getSize().x / 2, shape_.getSize().y / 2});
    shape_.setPosition(pos_->getPos());
    findRoute();
}

void Car::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(shape_, states);
}

void Car::update(float deltatime, const std::vector<std::unique_ptr<Car>> &cars)
{
    if (route_.size() < 1)
        return;

    if (VectorMath::Distance(shape_.getPosition(), route_.front()->getPos()) < 5.f)
    {
        shape_.setPosition(route_.front()->getPos());
        prev_ = std::make_shared<Node>(*route_.front());
        route_.pop_front();
        if (route_.size() < 1)
        {
            finished = true;
            return;
        }
        // We only need to change rotation of the car on turn
        dir_ = VectorMath::Normalize(route_.front()->getPos() - prev_->getPos());
        shape_.setRotation(VectorMath::Angle(dir_, {0, 1.f}) * 180.f / M_PI);
    }
    // Checks if there is something (another car) infront of this car
    // if there is -> we cant move forward
    if (frontEmpty(cars))
        shape_.move(dir_ * deltatime * speed_);
}

bool Car::frontEmpty(const std::vector<std::unique_ptr<Car>> &cars) const
{
    for (const auto &car : cars)
    {
        // safe distance to the car infront
        if (car->shape_.getGlobalBounds().contains(shape_.getPosition() + dir_ * shape_.getSize().y))
            return false;
        // car front
        if (car->shape_.getGlobalBounds().contains(shape_.getPosition() + dir_ * shape_.getSize().y * 0.51f))
            return false;
    }
    return true;
}

void Car::findRoute()
{
    std::map<std::shared_ptr<Node>, bool> visited;
    pos_->search_DFS(pos_, dest_, visited, route_);
}
} // namespace TrafficSim
