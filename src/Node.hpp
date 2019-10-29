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
    Node(const sf::Vertex &vertex_);
    // This makes one way connection
    void connectTo(Node *other_node);
    // Two way connection
    void connectWith(Node *another_node);

    //Getters
    const std::vector<Node *> &getNeighbors() const { return neighbors_; }
    sf::Vector2f getPos() const { return vertex_.position; }

private:
    // Stores position and color
    const sf::Vertex vertex_;
    //All nodes that this node is connected to
    //Not sure if this should be shared_ptr
    std::vector<Node *> neighbors_;
};
} // namespace TrafficSim
