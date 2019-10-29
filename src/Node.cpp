#include "Node.hpp"

namespace TrafficSim
{
Node::Node(const sf::Vertex &vertex) : vertex_(vertex)
{
}

void Node::connectTo(Node *other_node)
{
    neighbors_.push_back(other_node);
}

void Node::connectWith(Node *other_node)
{
    connectTo(other_node);
    other_node->connectTo(this);
}

} // namespace TrafficSim