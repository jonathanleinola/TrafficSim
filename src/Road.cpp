#include "Road.hpp"

#include <iostream>

namespace TrafficSim
{

Road::Road(const std::shared_ptr<Node> &begin, const std::shared_ptr<Node> &end, float lane_width, const sf::Texture &texture)
    : begin_(begin), end_(end), dir_(VectorMath::Normalize(end_->getPos() - begin_->getPos())), lane_width_(lane_width), road_texture_(texture)
{
    // TODO- when combining roads nodes are not connected correctly
    init();
}

Road::Road(const Road &prev_road, const std::shared_ptr<Node> &end)
    : begin_(prev_road.brNode_), end_(end), dir_(VectorMath::Normalize(end_->getPos() - begin_->getPos())), lane_width_(prev_road.lane_width_)
{
    init();
}



bool Road::isHorizontal() const
{
    return abs(dir_.x) > abs(dir_.y);
}

void Road::createIntersection(Road &another, const sf::Vector2f &pos, std::shared_ptr<Node> *intersection_nodes)
{
    // intersection nodes top left, torright, bot right, bot left.
    std::shared_ptr<Node> &itlNode = intersection_nodes[0];
    std::shared_ptr<Node> &itrNode = intersection_nodes[1];
    std::shared_ptr<Node> &ibrNode = intersection_nodes[2];
    std::shared_ptr<Node> &iblNode = intersection_nodes[3];

    if (itlNode == nullptr)
        itlNode = std::make_shared<Node>(sf::Vector2f(pos.x - lane_width_ * 0.5f, pos.y - lane_width_ * 0.5f));

    if (itrNode == nullptr)
        itrNode = std::make_shared<Node>(sf::Vector2f(pos.x + lane_width_ * 0.5f, pos.y - lane_width_ * 0.5f));

    if (ibrNode == nullptr)
        ibrNode = std::make_shared<Node>(sf::Vector2f(pos.x + lane_width_ * 0.5f, pos.y + lane_width_ * 0.5f));

    if (iblNode == nullptr)
        iblNode = std::make_shared<Node>(sf::Vector2f(pos.x - lane_width_ * 0.5f, pos.y + lane_width_ * 0.5f));

    //Disconnect old connections
    brNode_->disconnect(erNode_);
    blNode_->disconnect(elNode_);

    //Connect them to new nodes

    if (isHorizontal())
    {
        // ->
        if (dir_.x > 0)
        {
            brNode_->connect(iblNode);
            blNode_->connect(itrNode);
            //Intersection nodes
            itlNode->connect(elNode_);
            ibrNode->connect(erNode_);
        }
        // <-
        else
        {
            brNode_->connect(itrNode);
            blNode_->connect(iblNode);
            //Intersection nodes
            itlNode->connect(erNode_);
            ibrNode->connect(elNode_);
        }
    }
    else
    {
        // v
        if (dir_.y > 0)
        {
            brNode_->connect(itlNode);
            blNode_->connect(ibrNode);
            //Intersection nodes
            itrNode->connect(elNode_);
            iblNode->connect(erNode_);
        }
        // ^
        else
        {
            brNode_->connect(ibrNode);
            blNode_->connect(itlNode);
            //Intersection nodes
            itrNode->connect(erNode_);
            iblNode->connect(elNode_);
        }
    }
}


void Road::init()
{
    //Perpendicular direction to m_dir.
    // We need this vector to make our 1 dimensional line from point begin_ to point end_, 2-d road
    sf::Vector2f pdir(-dir_.y, dir_.x);

    brNode_ = std::make_shared<Node>(begin_->getPos() + pdir * lane_width_ * 0.5f, sf::Color::Blue);
    blNode_ = std::make_shared<Node>(end_->getPos() - pdir * lane_width_ * 0.5f, sf::Color::Blue);

    erNode_ = std::make_shared<Node>(brNode_->getPos() + (end_->getPos() - begin_->getPos()));
    elNode_ = std::make_shared<Node>(blNode_->getPos() - (end_->getPos() - begin_->getPos()));
    // Connect begin nodes to their same lane end nodes
    brNode_->connect(erNode_);
    blNode_->connect(elNode_);

    // Drawing stuff

    vertices_.reserve(4);
    vertices_.emplace_back(begin_->getPos() + pdir * lane_width_);
    vertices_.emplace_back(begin_->getPos() - pdir * lane_width_);
    vertices_.emplace_back(end_->getPos() + pdir * lane_width_);
    vertices_.emplace_back(end_->getPos() - pdir * lane_width_);

    vertices_[0].texCoords = sf::Vector2f(0,0);
    vertices_[1].texCoords = sf::Vector2f(100,0);
    vertices_[2].texCoords = sf::Vector2f(0,1000);
    vertices_[3].texCoords = sf::Vector2f(100,1000);
}

void Road::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.texture = &road_texture_;
    target.draw(&vertices_[0], vertices_.size(), sf::TriangleStrip, states);
    // Drawing the for debuggin purposes
    target.draw(*brNode_);
    target.draw(*blNode_);
    target.draw(*erNode_);
    target.draw(*elNode_);
}

} // namespace TrafficSim
