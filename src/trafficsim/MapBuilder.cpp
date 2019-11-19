#include "MapBuilder.hpp"

#include <string>
#include <memory>
#include <iostream>

namespace TrafficSim
{

MapBuilder::MapBuilder(Map &map, const Window &window)
    : map_(map), window_(window)
{
}

const char *editing_mode(EditingOption mode)
{
    return (const char *[]){
        "Inspect",
        "Add road",
        "Remove",
        "Rotate",
        "Flip",
        "Add light"}[mode];
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
    if (editing_option_ == EditingOption::AddRoad)
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
    if (selected_tile_index != UINT_MAX && map_.getGrid().getTile(selected_tile_index)->getType() != TileType::Empty)
    {
        ImGui::SetNextWindowPos(select_menu_pos_);
        ImGui::Begin("Tile Editor");
        ImGui::BeginColumns("", 2);
        for (int i = 0; i != TileType::Empty; i++)
        {
            TileType road_type = static_cast<TileType>(i);
            if (ImGui::RadioButton(road_type_name(road_type), map_.getGrid().getTile(selected_tile_index)->getType() == road_type))
                addRoad(map_.getGrid().getTile(selected_tile_index)->getCenter(), road_type);
        }
        ImGui::NextColumn();
        if (ImGui::Button("Rotate"))
            rotateRoad(map_.getGrid().getTile(selected_tile_index)->getCenter());
        if (ImGui::Button("Flip"))
            flipRoad(map_.getGrid().getTile(selected_tile_index)->getCenter());
        if (ImGui::Button("Remove"))
            removeRoad(map_.getGrid().getTile(selected_tile_index)->getCenter());
        ImGui::EndColumns();
        ImGui::End();
    }
}

void MapBuilder::addRoad(const sf::Vector2f &pos, TileType type)
{
    auto &tile = map_.getGrid().getTile(pos);
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
    auto arr = map_.getGrid().getNeigborTiles(tile->getTileIndex());
    r->autoRotate(arr);

    tile.swap(road_tile);
    connectRoads();
}

void MapBuilder::addTrafficLight(const sf::Vector2f &pos)
{
    auto &tile = map_.getGrid().getTile(pos);
    if (!tile || tile->getType() != StraightRoadType)
        return;

    RoadTile *road = static_cast<RoadTile *>(tile.get());
    map_.addLight(road);
}

void MapBuilder::removeRoad(const sf::Vector2f &pos)
{
    auto &tile = map_.getGrid().getTile(pos);
    if (!tile || tile->getType() == TileType::Empty)
        return;
    RoadTile *road = static_cast<RoadTile*>(tile.get());
    map_.removeLight(road);
    std::unique_ptr<Tile> empty_tile = std::make_unique<Tile>(tile->getPos(), tile->getSize(), tile->getTileIndex());
    tile.swap(empty_tile);
    connectRoads();
}
void MapBuilder::rotateRoad(const sf::Vector2f &pos)
{
    auto &tile = map_.getGrid().getTile(pos);
    if (!tile || tile->getType() == TileType::Empty)
        return;

    RoadTile *road_tile = static_cast<RoadTile *>(tile.get());
    road_tile->rotate();
    connectRoads();
}

void MapBuilder::flipRoad(const sf::Vector2f &pos)
{
    auto &tile = map_.getGrid().getTile(pos);
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
        auto arr = map_.getGrid().getNeigborTiles(tile->getTileIndex());
        road_tile->connect(arr);
    }
}

void MapBuilder::connectRoads()
{
    for (unsigned int i = 0; i < map_.getGrid().getSize(); ++i)
    {
        auto &tile = map_.getGrid().getTile(i);
        connectRoad(tile);
    }
}

void MapBuilder::clearMap()
{
    map_.getGrid().init();
    connectRoads();
}
/*
*   Builder input
*/

void MapBuilder::selectTile(const sf::Vector2f &pos)
{
    auto &new_tile = map_.getGrid().getTile(pos);
    if (!new_tile)
    {
        unSelectTile();
        return;
    }
    if (new_tile->getTileIndex() == selected_tile_index)
    {
        new_tile->unSelectTile();
        selected_tile_index = UINT_MAX;
    }
    else
    {
        new_tile->selectTile();
        unSelectTile();
        selected_tile_index = new_tile->getTileIndex();
        select_menu_pos_ = window_.convert(new_tile->getPos() + sf::Vector2f(new_tile->getSize(), 0.f));
    }
}

void MapBuilder::unSelectTile()
{
    if (selected_tile_index != UINT_MAX)
        map_.getGrid().getTile(selected_tile_index)->unSelectTile();
    selected_tile_index = UINT_MAX;
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
        if (ev.mouseButton.button == sf::Mouse::Right)
        {
            switch (editing_option_)
            {
            case AddRoad:
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
            case AddLight:
                addTrafficLight(pos);
                break;
            default:
                break;
            }
            unSelectTile();
        }
        else if (ev.mouseButton.button == sf::Mouse::Left)
        {
            selectTile(pos);
        }
    }
    else if (ev.type == sf::Event::MouseMoved)
    {
        sf::Vector2f pos = window_.convert(sf::Vector2i(ev.mouseMove.x, ev.mouseMove.y));
        auto &new_tile = map_.getGrid().getTile(pos);
        if (!new_tile)
            return;
        if (selected_tile_index != new_tile->getTileIndex())
        {
            if (hovered_tile_index != UINT_MAX)
                if (hovered_tile_index != selected_tile_index)
                    map_.getGrid().getTile(hovered_tile_index)->unSelectTile();
            new_tile->hoverTile();
            hovered_tile_index = new_tile->getTileIndex();
        }
    }
}

} // namespace TrafficSim