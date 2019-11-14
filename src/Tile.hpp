#pragma once

#include <SFML/Graphics.hpp>

#include "VectorMath.hpp"
#include "Node.hpp"

namespace TrafficSim
{

enum TileType
{
    Empty,
    StraightRoadType,
    RoadTurnType,
    IntersectionType,
    TrisectionType
};

enum NeighborIndex
{
    UP = 0,
    RIGHT,
    DOWN,
    LEFT
};

class Tile : public sf::Drawable
{
public:
    Tile(const sf::Vector2f &pos, float size, unsigned int tile_index);

    const sf::Vector2f &getPos() const { return pos_; };
    sf::Vector2f getCenter() const;
    unsigned int getTileIndex() const { return tile_index_; }
    float getSize() const { return size_; }

    void selectTile();
    void unSelectTile();

    std::shared_ptr<Node> getNode() const { return node_; }
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    virtual TileType getType() const { return TileType::Empty; }

protected:
    std::shared_ptr<Node> node_;
    sf::Vector2f pos_;
    float size_;
    sf::RectangleShape rect_;
    unsigned int tile_index_;
    // Up: { 0, 1 }, Right { 1, 0 }, Down { 0, -1 }, Left { -1, 0 }
};
} // namespace TrafficSim
