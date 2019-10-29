#pragma once

#include <vector> //std::vector
#include <memory> //std::shared_ptr

#include <SFML/Graphics/Vertex.hpp>

namespace TrafficSim
{
class Node
{

public:
    //Default constructor
    Node(const sf::Vector2f &position);
    // This creates one way connection
    void connectTo(std::shared_ptr<Node> &another);

    //Getters
    const std::vector<std::shared_ptr<Node>> &getNeighbors() const { return neighbors_; }
    sf::Vector2f getPos() const { return position_; }

private:
    // Stores position
    const sf::Vector2f position_;
    //All nodes that this node is connected to
    std::vector<std::shared_ptr<Node>> neighbors_;
};
} // namespace TrafficSim
