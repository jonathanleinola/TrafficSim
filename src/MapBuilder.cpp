#include "MapBuilder.hpp"

#include <string>
#include <memory>
#include <iostream>

namespace TrafficSim
{

MapBuilder::MapBuilder(Grid &grid)
    : grid_(grid)
{
}

void MapBuilder::drawGUI()
{
    ImGui::Begin("Map Editor");
    std::string mode = "Current mode: ";
    switch (editing_mode_)
    {
    case EditingMode::Select:
        mode += "Select";
        break;
    case EditingMode::Add:
        mode += "Add";
        break;
    case EditingMode::Remove:
        mode += "Remove";
        break;
    case EditingMode::Rotate:
        mode += "Rotate";
        break;
    }
    ImGui::Text(mode.c_str());
    if (ImGui::Button("Select"))
    {
        editing_mode_ = EditingMode::Select;
    }
    if (ImGui::Button("Add"))
    {
        editing_mode_ = EditingMode::Add;
    }
    if (ImGui::Button("Remove"))
    {
        editing_mode_ = EditingMode::Remove;
    }
    if (ImGui::Button("Rotate"))
    {
        editing_mode_ = EditingMode::Rotate;
    }
    ImGui::End();
}

void MapBuilder::handleInput(const sf::Event &ev)
{
    if (!building_mode_)
        return;
    if (ev.type == sf::Event::MouseButtonPressed)
    {
        switch (editing_mode_)
        {
        case EditingMode::Select:
            selectTile(sf::Vector2f(ev.mouseButton.x, ev.mouseButton.y));
            break;
        case EditingMode::Add:
            addRoad(sf::Vector2f(ev.mouseButton.x, ev.mouseButton.y));
            break;
        case EditingMode::Remove:
            removeRoad(sf::Vector2f(ev.mouseButton.x, ev.mouseButton.y));
            break;
        case EditingMode::Rotate:
            rotateRoad(sf::Vector2f(ev.mouseButton.x, ev.mouseButton.y));
            break;
        }
    }
}

void MapBuilder::selectTile(const sf::Vector2f &pos)
{
    auto &new_tile = grid_.getTile(pos);
    if (!new_tile)
        return;
    if (new_tile->getTileIndex() == selected_tile_)
    {
        new_tile->unSelectTile();
        selected_tile_ = UINT_MAX;
    }
    else
    {
        new_tile->selectTile();
        if (selected_tile_ != UINT_MAX)
            grid_.getTile(selected_tile_)->unSelectTile();
        selected_tile_ = new_tile->getTileIndex();
    }
}

void MapBuilder::addRoad(const sf::Vector2f &pos)
{
    auto &tile = grid_.getTile(pos);
    if (!tile || tile->getType() == TileType::RoadType)
        return;
    std::unique_ptr<Tile> road_tile = std::make_unique<RoadTile>(*tile);
    tile.swap(road_tile);
    connectRoads();
}
void MapBuilder::removeRoad(const sf::Vector2f &pos)
{
    auto &tile = grid_.getTile(pos);
    if (!tile || tile->getType() != TileType::RoadType)
        return;
    std::unique_ptr<Tile> empty_tile = std::make_unique<Tile>(tile->getPos(), tile->getSize(), tile->getTileIndex());
    tile.swap(empty_tile);
    connectRoads();
}
void MapBuilder::rotateRoad(const sf::Vector2f &pos)
{
    auto &tile = grid_.getTile(pos);
    if (!tile || tile->getType() != TileType::RoadType)
        return;
    if (tile->getType() == TileType::RoadType)
        tile->rotate();

    connectRoads();
}

void MapBuilder::connectToNeighbor(std::unique_ptr<Tile> &tile, std::unique_ptr<Tile> &neighbor)
{
    if (neighbor && neighbor->getType() == TileType::RoadType)
    {
        if (tile->getDir() == neighbor->getDir())
        {
            tile->getNode()->connect(neighbor->getNode());
            std::cout << "Tile connected" << std::endl;
        }
    }
}

void MapBuilder::connectRoad(std::unique_ptr<Tile> &tile)
{
    if (tile && tile->getType() == TileType::RoadType)
    {
        tile->getNode()->disconnectAll();
        sf::Vector2f dir = tile->getDir();
        if (dir.x == 1)
        {
            auto &neighbor = grid_.getRightNeighbor(tile->getTileIndex());
            connectToNeighbor(tile, neighbor);
        }
        else if (dir.x == -1)
        {
            auto &neighbor = grid_.getLeftNeighbor(tile->getTileIndex());
            connectToNeighbor(tile, neighbor);
        }
        else if (dir.y == 1)
        {
            auto &neighbor = grid_.getUpNeighbor(tile->getTileIndex());
            connectToNeighbor(tile, neighbor);
        }
        else if (dir.y == -1)
        {
            auto &neighbor = grid_.getDownNeighbor(tile->getTileIndex());
            connectToNeighbor(tile, neighbor);
        }
    }
}

void MapBuilder::connectRoads()
{
    for (unsigned int i = 0; i < grid_.getSize(); ++i)
    {
        auto &tile = grid_.getTile(i);
        connectRoad(tile);
    }
}

} // namespace TrafficSim