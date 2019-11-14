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
    gui_hovered = ImGui::IsAnyWindowHovered();
    // Choose click mode
    if (ImGui::RadioButton("Select", editing_mode_ == EditingMode::Select))
        editing_mode_ = EditingMode::Select;

    if (ImGui::RadioButton("Add", editing_mode_ == EditingMode::Add))
        editing_mode_ = EditingMode::Add;

    if (ImGui::RadioButton("Remove", editing_mode_ == EditingMode::Remove))
        editing_mode_ = EditingMode::Remove;

    if (ImGui::RadioButton("Rotate", editing_mode_ == EditingMode::Rotate))
        editing_mode_ = EditingMode::Rotate;

    if (ImGui::RadioButton("Flip", editing_mode_ == EditingMode::Flip))
        editing_mode_ = EditingMode::Flip;

    // Choose road type to add
    ImGui::BeginChild("Road type", ImVec2(0, 0), true);
    if (editing_mode_ == EditingMode::Add)
    {
        ImGui::Text("Road type selected:");
        if (ImGui::RadioButton("Straight Road", selected_road_ == TileType::StraightRoadType))
            selected_road_ = TileType::StraightRoadType;
        if (ImGui::RadioButton("Road Turn", selected_road_ == TileType::RoadTurnType))
            selected_road_ = TileType::RoadTurnType;
        if (ImGui::RadioButton("Intersection", selected_road_ == TileType::IntersectionType))
            selected_road_ = TileType::IntersectionType;
        if (ImGui::RadioButton("Trisection", selected_road_ == TileType::TrisectionType))
            selected_road_ = TileType::TrisectionType;
        if (ImGui::RadioButton("Road Junction", selected_road_ == TileType::JunctionType))
            selected_road_ = TileType::JunctionType;
    }
    ImGui::EndChild();

    ImGui::End();
    if (selected_tile_ != UINT_MAX && grid_.getTile(selected_tile_)->getType() != TileType::Empty)
    {
        ImGui::Begin("Tile Editor");
        if (ImGui::RadioButton("Straight Road", grid_.getTile(selected_tile_)->getType() == TileType::StraightRoadType))
        {
            if (grid_.getTile(selected_tile_)->getType() == TileType::StraightRoadType)
                return;
            addRoad(grid_.getTile(selected_tile_)->getCenter(), StraightRoadType);
        }
        if (ImGui::RadioButton("Road Turn", grid_.getTile(selected_tile_)->getType() == TileType::RoadTurnType))
        {
            if (grid_.getTile(selected_tile_)->getType() == TileType::RoadTurnType)
                return;
            addRoad(grid_.getTile(selected_tile_)->getCenter(), RoadTurnType);
        }
        if (ImGui::RadioButton("Intersection", grid_.getTile(selected_tile_)->getType() == TileType::IntersectionType))
        {
            if (grid_.getTile(selected_tile_)->getType() == TileType::IntersectionType)
                return;
            addRoad(grid_.getTile(selected_tile_)->getCenter(), IntersectionType);
        }
        if (ImGui::RadioButton("Trisection", grid_.getTile(selected_tile_)->getType() == TileType::TrisectionType))
        {
            if (grid_.getTile(selected_tile_)->getType() == TileType::TrisectionType)
                return;
            addRoad(grid_.getTile(selected_tile_)->getCenter(), TrisectionType);
        }

        if (ImGui::RadioButton("Trisection", grid_.getTile(selected_tile_)->getType() == TileType::JunctionType))
        {
            if (grid_.getTile(selected_tile_)->getType() == TileType::JunctionType)
                return;
            addRoad(grid_.getTile(selected_tile_)->getCenter(), TileType::JunctionType);
        }
        ImGui::End();
    }
}

void MapBuilder::handleInput(const sf::Event &ev)
{
    if (!building_mode_)
        return;
    if (ev.type == sf::Event::MouseButtonPressed)
    {
        if (gui_hovered)
            return;
        switch (editing_mode_)
        {
        case Select:
            selectTile(sf::Vector2f(ev.mouseButton.x, ev.mouseButton.y));
            break;
        case Add:
            addRoad(sf::Vector2f(ev.mouseButton.x, ev.mouseButton.y), selected_road_);
            break;
        case Remove:
            removeRoad(sf::Vector2f(ev.mouseButton.x, ev.mouseButton.y));
            break;
        case Rotate:
            rotateRoad(sf::Vector2f(ev.mouseButton.x, ev.mouseButton.y));
            break;
        case Flip:
            flipRoad(sf::Vector2f(ev.mouseButton.x, ev.mouseButton.y));
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

void MapBuilder::addRoad(const sf::Vector2f &pos, TileType type)
{
    auto &tile = grid_.getTile(pos);
    if (!tile || tile->getType() == type)
        return;

    std::unique_ptr<Tile> road_tile;
    switch (type)
    {
    case StraightRoadType:
        road_tile = std::make_unique<StraightRoad>(*tile);
        break;
    case RoadTurnType:
        road_tile = std::make_unique<RoadTurn>(*tile);
        break;
    case IntersectionType:
        road_tile = std::make_unique<RoadIntersection>(*tile);
        break;
    case TrisectionType:
        road_tile = std::make_unique<RoadTrisection>(*tile);
        break;
    case JunctionType:
        road_tile = std::make_unique<RoadJunction>(*tile);
        break;
    default:
        break;
    }
    tile.swap(road_tile);
    connectRoads();
}
void MapBuilder::removeRoad(const sf::Vector2f &pos)
{
    auto &tile = grid_.getTile(pos);
    if (!tile || tile->getType() == TileType::Empty)
        return;
    std::unique_ptr<Tile> empty_tile = std::make_unique<Tile>(tile->getPos(), tile->getSize(), tile->getTileIndex());
    tile.swap(empty_tile);
    connectRoads();
}
void MapBuilder::rotateRoad(const sf::Vector2f &pos)
{
    auto &tile = grid_.getTile(pos);
    if (!tile || tile->getType() == TileType::Empty)
        return;

    RoadTile *road_tile = static_cast<RoadTile *>(tile.get());
    road_tile->rotate();
    connectRoads();
}

void MapBuilder::flipRoad(const sf::Vector2f &pos)
{
    auto &tile = grid_.getTile(pos);
    if (!tile || tile->getType() == TileType::Empty)
        return;

    RoadTile *road_tile = static_cast<RoadTile *>(tile.get());
    road_tile->flip();
    connectRoads();
}

void MapBuilder::connectRoad(std::unique_ptr<Tile> &tile)
{
    if (tile && tile->getType() != TileType::Empty)
    {
        tile->getNode()->disconnectAll();
        RoadTile *road_tile = static_cast<RoadTile *>(tile.get());
        auto arr = grid_.getNeigborTiles(tile->getTileIndex());
        road_tile->connect(arr);
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