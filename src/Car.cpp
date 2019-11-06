#include "Car.hpp"

namespace TrafficSim
{

 Car::Car(const std::shared_ptr<Node> &pos,const std::shared_ptr<Node> &dest,const sf::Vector2f &size)
   : pos_(pos),dest_(dest),shape_(size), speed_(100)
 {
     shape_.setOrigin({shape_.getSize().x /2, shape_.getSize().y /2});
     shape_.setPosition(pos_->getPos());
     shape_.setFillColor(sf::Color::Green);
     shape_.rotate(VectorMath::Angle(dest_->getPos(), pos_->getPos())*180/M_PI);
 }
    void Car::draw(sf::RenderTarget &target, sf::RenderStates states) const{
        target.draw(shape_,states);
    }

    void Car::update(float deltatime){
        sf::Vector2f dir=VectorMath::Normalize(dest_->getPos()-pos_->getPos());
        shape_.move(dir*deltatime*speed_);
    }
}

