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
     std::map<std::shared_ptr<Node>, bool> visited;
     findRoute(pos_, visited);
 }
    void Car::draw(sf::RenderTarget &target, sf::RenderStates states) const{
        target.draw(shape_,states);
    }

    void Car::update(float deltatime){
        if (step_ >= route_.size()) 
            return;
        if (VectorMath::Distance(shape_.getPosition(), route_.at(step_)->getPos()) < 5.f)
        {
            shape_.setPosition(route_.at(step_)->getPos());
            step_++;
            if (step_ >= route_.size()) 
                return;
        }
        sf::Vector2f dir=VectorMath::Normalize(route_.at(step_)->getPos()-pos_->getPos());
        
        shape_.move(dir*deltatime*speed_);
    }

    void Car::findRoute(const std::shared_ptr<Node> &cur, std::map<std::shared_ptr<Node>,bool> &visited)
    {
        if (visited[cur])
            return;
        visited[cur] = true;

        if (visited[dest_])
        {
            route_.push_back(cur);
            return;
        }
        for (const auto &neighbor : cur->getNeighbors())
        {
           findRoute(neighbor, visited);
        }
        
    }
}

