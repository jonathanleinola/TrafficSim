#pragma once
#include <memory>

#include <SFML/Graphics.hpp>

#include "Node.hpp"


namespace TrafficSim
{

class Car : public sf::Drawable
{
public:
    Car(const std::shared_ptr<Node> &pos,const std::shared_ptr<Node> &dest,const sf::Vector2f &size);
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void update(float deltatime); //deltatime is time from the last update
private:
    const std::shared_ptr<Node> pos_, dest_;

    float speed_, acceleration_;
    sf::RectangleShape shape_;
};

}