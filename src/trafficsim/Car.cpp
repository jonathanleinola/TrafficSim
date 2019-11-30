#include "Car.hpp"

#include <iostream>
#include <algorithm> // std::max
#include "Rando.hpp"

namespace TrafficSim
{

std::vector<const sf::Texture *> Car::Textures_;

Car::Car(const std::shared_ptr<Node> &pos, const std::shared_ptr<Node> &dest, const sf::Vector2f &size)
    : pos_(pos), dest_(dest), prev_(pos), shape_(size), speed_(200), acceleration_(0)
{
    Rando r(Textures_.size());
    int r_i = r.uniroll();
    shape_.setTexture(Textures_.at(r_i-1));
    shape_.setOrigin({shape_.getSize().x / 2, shape_.getSize().y / 2});
    shape_.setPosition(pos_->getPos());
    findRoute();
}

void Car::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(shape_, states);
}

void Car::AddTexture(const sf::Texture *carTexture)
{
    Textures_.push_back(carTexture);
}

void Car::update(const sf::Time &game_time, float deltatime, const std::vector<std::unique_ptr<Car>> &cars, const std::vector<std::unique_ptr<TrafficLightHandler>> &light_handlers)
{
    if (route_.size() < 1)
    {
        finished = true;
        return;
    }

    float delta_step = deltatime * speed_;
    if (VectorMath::Distance(shape_.getPosition(), route_.front()->getPos()) < delta_step)
    {
        // Increment node cars_passed counter
        prev_->incrementCounter(game_time);
        shape_.setPosition(route_.front()->getPos());
        prev_ = route_.front();
        route_.pop_front();
        if (route_.size() < 1)
        {
            finished = true;
            return;
        }
        // We only need to change rotation of the car on turn
        dir_ = VectorMath::Normalize(route_.front()->getPos() - prev_->getPos());
        if (dir_.x == 1)
            shape_.setRotation(90);
        else if (dir_.x == -1)
            shape_.setRotation(270);
        else if (dir_.y == -1)
            shape_.setRotation(0);
        else if (dir_.y == 1)
            shape_.setRotation(180);
    }
    // Checks if there is something (another car) infront of this car
    // if there is -> we cant move forward
    if (frontEmpty(cars, light_handlers))
        shape_.move(dir_ * deltatime * speed_);
}

bool Car::frontEmpty(const std::vector<std::unique_ptr<Car>> &cars, const std::vector<std::unique_ptr<TrafficLightHandler>> &light_handlers) const
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
    for (const auto &light_manager : light_handlers)
    {
        const auto &lights = light_manager->getLights();
        for (const auto &light : lights)
        {
            if (!light->canDrive())
            {
                if (light->getBlocker().getGlobalBounds().contains(shape_.getPosition() + dir_ * shape_.getSize().y))
                    return false;
                // car front
                if (light->getBlocker().getGlobalBounds().contains(shape_.getPosition() + dir_ * shape_.getSize().y * 0.51f))
                    return false;
            }
            // light infront
        }
    }
    return true;
}

void Car::findRoute()
{
    std::map<std::shared_ptr<Node>, bool> visited;
    Node::search_AStar(pos_, dest_, visited, route_);
}
} // namespace TrafficSim
