#include "Node.hpp"

#include <iostream>

namespace TrafficSim
{

Node::Node(const sf::Vector2f &position)
    : position_(position), shape_(6.f)
{
    shape_.setOrigin(3.f, 3.f);
    shape_.setPosition(position_);

    // Color will be Red by default (Debugging only)
    shape_.setFillColor(sf::Color::Red);

    // Init vector
    cars_passed_.reserve(Samples_);
    for (unsigned int i = 0; i < Samples_; ++i)
        cars_passed_.emplace_back(0);

}


void Node::incrementCounter(const sf::Time &game_time) const
{
    // Seconds in day divided by seconds per Samples per day will get seconds in sample
    const unsigned int window = 24 * 60 * 60 / Samples_;
    float g_time = game_time.asSeconds();
    unsigned int index = g_time / window;
    try
    {
        ++cars_passed_.at(index);
    }
    catch (const std::out_of_range &e)
    {
        std::cout << "Error when tried to access cars_passed_ array at index: " << index << std::endl;
        std::cout << e.what() << std::endl;
    }
}

void Node::resetCounter() const
{
    for (unsigned int i = 0; i < Samples_; ++i)
        cars_passed_[i] = 0;
}

void Node::search_DFS(const std::shared_ptr<Node> &cur, const std::shared_ptr<Node> &dest, std::map<std::shared_ptr<Node>, bool> &visited, std::list<std::shared_ptr<Node>> &path) const
{
    if (visited[cur])
        return;
    visited[cur] = true;
    path.push_back(cur);
    if (cur == dest)
    {
        return;
    }
    for (const auto &neighbor : cur->getNeighbors())
    {
        if (!visited[dest])
            search_DFS(neighbor, dest, visited, path);
    }
    if (!visited[dest])
        path.pop_back();
}

float Node::pathDistance(const std::shared_ptr<Node> &node) const
{
}

void Node::connect(const std::shared_ptr<Node> &another)
{
    neighbors_.push_back(another);
}

void Node::disconnectAll()
{
    neighbors_.clear();
}

void Node::disconnect(const std::shared_ptr<Node> &node)
{
    // Only C++ 14
    neighbors_.erase(std::remove_if(neighbors_.begin(), neighbors_.end(), [&node](const auto &n) -> bool { return n == node; }), neighbors_.end());

    // C++ 11
    // for (auto it = neighbors_.begin(); it != neighbors_.end(); ++it)
    // {
    //     if (node == *it)
    //     {
    //         neighbors_.erase(it);
    //         return;
    //     }
    // }
}

void Node::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    //target.draw(shape_, states);
}

std::ostream &operator<<(std::ostream &os, const Node *node)
{
    if (node)
        os << "Node at: (" << node->getPos().x << ", " << node->getPos().y << ") has " << node->getNeighbors().size() << " neighbors.";
    else
        os << "Node is nullptr.";
    return os;
}

} // namespace TrafficSim