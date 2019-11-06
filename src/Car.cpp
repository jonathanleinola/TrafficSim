#include "Car.hpp"

namespace TrafficSim
{

 Car::Car(const std::shared_ptr<Node> &pos,const std::shared_ptr<Node> &dest,const sf::Vector2f &size)
   : pos_(pos),dest_(dest),shape_(size)
 {
     shape_.setOrigin({shape_.getSize().x /2, shape_.getSize().y /2});
     shape_.setPosition(pos_->getPos());
     shape_.setFillColor(sf::Color::Green);
     
 }
    void Car::draw(sf::RenderTarget &target, sf::RenderStates states) const{
        target.draw(shape_,states);
    }

    void Car::update(float deltatime){

    }
}

