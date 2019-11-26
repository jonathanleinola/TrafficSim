#pragma once

#include <list>         //std::list
#include <vector>       //std::vector
#include <memory>       //std::shared_ptr
#include <algorithm>    //std::remove_if
#include <cstdint>      //std::uint8_t

#include <SFML/Graphics.hpp>


namespace TrafficSim
{
class Node : public sf::Drawable
{

public:
    //Default constructor
    Node(const sf::Vector2f &position);


    // Creates one way connection, by adding "another" to neighbors_
    void connect(const std::shared_ptr<Node> &another);
    // Removes connection, by erasing "node" from neighbors_
    void disconnect(const std::shared_ptr<Node> &node);
    // Removes all nodes from neighbors_
    void disconnectAll();

    // Searching algorithms
    void search_DFS(const std::shared_ptr<Node> &cur, const std::shared_ptr<Node> &dest, std::map<std::shared_ptr<Node>, bool> &visited, std::list<std::shared_ptr<Node>> &path) const;

    //Getters
    const sf::Vector2f &getPos() const { return position_; }
    const std::vector<std::shared_ptr<Node>> &getNeighbors() const { return neighbors_; }
    //Returns -1 if there is no path to node Uses DFS-algorithm
    float pathDistance(const std::shared_ptr<Node> &node) const;

    void incrementCounter(const sf::Time &game_time) const;
    std::uint8_t getLastCount(const sf::Time &game_time) const;
    void resetCounter() const;

    // Its drawable only for debugging purpouses
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    // Stores position
    const sf::Vector2f position_;
    //All nodes that this node is connected to
    // TODO - std::weak_ptr might be good for this
    std::vector<std::shared_ptr<Node>> neighbors_;

    // For statistics
    // 4 samples per hour -> 96 per day
    static constexpr unsigned int Samples_ = 96;
    // Statistic of whole day
    mutable std::vector<std::uint8_t> cars_passed_;

    // For debugging
    sf::CircleShape shape_;

};

std::ostream &operator<<(std::ostream &os, const Node *node);
} // namespace TrafficSim
