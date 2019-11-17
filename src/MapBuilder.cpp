#include "MapBuilder.hpp"

#include <string>
#include <memory>
#include <iostream>

namespace TrafficSim
{

MapBuilder::MapBuilder(Grid &grid, const Window &window)
    : grid_(grid), window_(window)
{
}

const char *editing_mode(EditingOption mode)
{
    return (const char *[]){
        "Inspect",
        "Add",
        "Remove",
        "Rotate",
        "Flip"}[mode];
}

const char *road_type_name(TileType type)
{
    return (const char *[]){
        "Straight Road",
        "Road Turn",
        "Intersection",
        "Trisection",
        "Road Junction"}[type];
}

void MapBuilder::drawGUI()
{
    ImGui::Begin("Map Editor");
    gui_hovered = ImGui::IsAnyWindowHovered();

    // Choose click mode
    for (int i = 0; i != EditingOption::ModeCount; i++)
    {
        EditingOption mode = static_cast<EditingOption>(i);
        if (ImGui::RadioButton(editing_mode(mode), editing_option_ == mode))
            editing_option_ = mode;
    }

    // Choose road type to add
    ImGui::BeginChild("Road type", ImVec2(0, 0), true);
    if (editing_option_ == EditingOption::Add)
    {
        ImGui::Text("Road type selected:");
        for (int i = 0; i != TileType::Empty; i++)
        {
            TileType road_type = static_cast<TileType>(i);
            if (ImGui::RadioButton(road_type_name(road_type), road_option_ == road_type))
                road_option_ = road_type;
        }
    }
    ImGui::EndChild();
    ImGui::End();

    // Left-click option menu
    if (selected_tile_index != UINT_MAX && grid_.getTile(selected_tile_index)->getType() != TileType::Empty)
    {
        ImGui::SetNextWindowPos(select_menu_pos_);
        ImGui::Begin("Tile Editor");
        ImGui::BeginColumns("", 2);
        for (int i = 0; i != TileType::Empty; i++)
        {
            TileType road_type = static_cast<TileType>(i);
            if (ImGui::RadioButton(road_type_name(road_type), grid_.getTile(selected_tile_index)->getType() == road_type))
                addRoad(grid_.getTile(selected_tile_index)->getCenter(), road_type);
        }
        ImGui::NextColumn();
        if (ImGui::Button("Rotate"))
            rotateRoad(grid_.getTile(selected_tile_index)->getCenter());
        if (ImGui::Button("Flip"))
            flipRoad(grid_.getTile(selected_tile_index)->getCenter());
        if (ImGui::Button("Remove"))
            removeRoad(grid_.getTile(selected_tile_index)->getCenter());
        ImGui::EndColumns();
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
        sf::Vector2f pos = window_.convert(sf::Vector2i(ev.mouseButton.x, ev.mouseButton.y));
        if (ev.mouseButton.button == sf::Mouse::Left)
        {
            switch (editing_option_)
            {
            case Add:
                addRoad(pos, road_option_);
                break;
            case Remove:
                removeRoad(pos);
                break;
            case Rotate:
                rotateRoad(pos);
                break;
            case Flip:
                flipRoad(pos);
                break;
            default:
                break;
            }
        }
        else if (ev.mouseButton.button == sf::Mouse::Right)
        {
            selectTile(pos);
        }
    }
}

void MapBuilder::selectTile(const sf::Vector2f &pos)
{
    auto &new_tile = grid_.getTile(pos);
    if (!new_tile)
        return;
    if (new_tile->getTileIndex() == selected_tile_index)
    {
        new_tile->unSelectTile();
        selected_tile_index = UINT_MAX;
    }
    else
    {
        new_tile->selectTile();
        if (selected_tile_index != UINT_MAX)
            grid_.getTile(selected_tile_index)->unSelectTile();
        selected_tile_index = new_tile->getTileIndex();
        select_menu_pos_ = window_.convert(new_tile->getPos() + sf::Vector2f(new_tile->getSize(), 0.f));
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
    RoadTile *r = static_cast<RoadTile *>(road_tile.get());
    auto arr = grid_.getNeigborTiles(tile->getTileIndex());
    r->autoRotate(arr);

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
    // TODO - Do we need to disconnect empty tiles when clearing?
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

void MapBuilder::clearMap()
{
    grid_.init();
    connectRoads();
}

} // namespace TrafficSim