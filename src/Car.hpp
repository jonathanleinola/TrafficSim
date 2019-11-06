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
    Car(const std::shared_ptr<Node> &pos,const std::shared_ptr<Node> &dest,const sf::Vector2f &size);
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void update(float deltatime); //deltatime is time from the last update
private:
    const std::shared_ptr<Node> pos_, dest_;
    std::vector<std::shared_ptr<Node>> route_;
    unsigned int step_ = 0;
    float speed_, acceleration_;
    sf::RectangleShape shape_;
    void findRoute(const std::shared_ptr<Node> &cur, std::map<std::shared_ptr<Node>, bool> &visited);
};

}