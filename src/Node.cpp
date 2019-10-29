#include "Node.hpp"

namespace TrafficSim
{
Node::Node(const sf::Vector2f &position) : position_(position)
{
}

void Node::connectTo(std::shared_ptr<Node> &another)
{
    neighbors_.push_back(another);
}

} // namespace TrafficSim