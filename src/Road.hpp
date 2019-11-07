#pragma once

#include <SFML/Graphics.hpp>

#include "VectorMath.hpp"
#include "Node.hpp"

namespace TrafficSim
{

// Road is just a straight line, which can be horizontal or diagonal atm
class Road : public sf::Drawable
{
public:
    // Creating new road which will not be connected to anything by default
    Road(const std::shared_ptr<Node> &begin, const std::shared_ptr<Node> &end, float lane_width);

    // When we are extending existing road in the same direction
    Road(const Road &prev_road, const std::shared_ptr<Node> &end);

    void createIntersection(Road& another, const sf::Vector2f& pos, std::shared_ptr<Node> *intersection_nodes);

    //Getters
    bool isHorizontal() const;
    const sf::Vector2f& getDir() const { return dir_; }
    std::pair<sf::Vector2f, sf::Vector2f> getEndPoints() const { return {begin_->getPos(), end_->getPos()}; }
    std::pair<std::shared_ptr<Node>, std::shared_ptr<Node>> getLaneBeginNodes() const { return {brNode_, blNode_}; }
    std::pair<std::shared_ptr<Node>, std::shared_ptr<Node>> getLaneEndNodes() const { return {erNode_, elNode_}; }

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    // TODO: these are depending on how road was defined. Maybe we could them fixed always to one corner no matter how begin- and endnode was given?
    std::shared_ptr<Node> brNode_, blNode_, erNode_, elNode_;
    
    //So we can draw them
    std::vector<sf::Vertex> vertices_;
    //These define road
    std::shared_ptr<Node> begin_, end_;

    sf::Vector2f dir_;

    float lane_width_;

    void init();
};
} // namespace TrafficSim
