#pragma once
#include <memory>
#include <SFML/Graphics.hpp>

#include "Node.hpp"
#include "VectorMath.hpp"

namespace TrafficSim
{

class Car : public sf::Drawable
{
public:
    Car(const std::shared_ptr<Node> &pos, const std::shared_ptr<Node> &dest, const sf::Vector2f &size, const sf::Texture &carTexture);

    // Called every frame to move car
    void update(float deltatime, const std::vector<std::unique_ptr<Car>> &cars); //deltatime is time from the last update

    // returns true if car is at its destination
    bool isFinished() const { return finished; }

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    const std::shared_ptr<Node> pos_, dest_;
    // Tracks previous node
    std::shared_ptr<Node> prev_;
    // Path from beginning node (where car is created) to dest_ node
    std::list<std::shared_ptr<Node>> route_;
    float speed_, acceleration_;
    sf::RectangleShape shape_;
    bool finished = false;
    sf::Vector2f dir_;

    void findRoute();
    // returns true if there is nothing infront of the car
    bool frontEmpty(const std::vector<std::unique_ptr<Car>> &cars) const;
};

} // namespace TrafficSim