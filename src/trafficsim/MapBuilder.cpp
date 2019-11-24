#include "MapBuilder.hpp"

#include <string>
#include <memory>
#include <iostream>

#include "imgui.h"
#include "imgui-SFML.h"
#include "imgui_internal.h"

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
    if (!building_mode_)
        return;
    ImGui::Begin("Map Editor");

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
    if (selected_tile_index_ != UINT_MAX && map_.grid_.getTile(selected_tile_index_)->getType() != TileType::Empty)
    {
        ImGui::SetNextWindowPos(select_menu_pos_);
        ImGui::Begin("Tile Editor");
        sf::Vector2i another_pos(select_menu_pos_.x, select_menu_pos_.y + ImGui::GetWindowHeight());
        ImGui::BeginColumns("", 2);
        for (int i = 0; i != TileType::Empty; i++)
        {
            TileType road_type = static_cast<TileType>(i);
            if (ImGui::RadioButton(road_type_name(road_type), map_.grid_.getTile(selected_tile_index_)->getType() == road_type))
                addRoad(map_.grid_.getTile(selected_tile_index_)->getCenter(), road_type);
        }
        ImGui::NextColumn();
        if (ImGui::Button("Rotate"))
            rotateRoad(map_.grid_.getTile(selected_tile_index_)->getCenter());
        if (ImGui::Button("Flip"))
            flipRoad(map_.grid_.getTile(selected_tile_index_)->getCenter());
        if (ImGui::Button("Remove"))
            removeRoad(map_.grid_.getTile(selected_tile_index_)->getCenter());
        // Traffic light editor
        ImGui::EndColumns();
        ImGui::End();
        RoadTile *road_tile = dynamic_cast<RoadTile *>(map_.grid_.getTile(selected_tile_index_));
        ImGui::SetNextWindowPos(another_pos);
        ImGui::Begin("Traffic Light editor");
        if (road_tile && road_tile->getLight())
        {
            int time = road_tile->getLight()->green_time_;
            if (ImGui::SliderInt("Green time", &time, 0.f, 100.f, "%.0f"))
                road_tile->getLight()->green_time_ = time;
            if (ImGui::Button("Remove Light"))
            {
                map_.removeLight(road_tile->getLight());
                road_tile->removeLight();
            }
            if (ImGui::Button("New handler"))
            {
                map_.newLightHandler(road_tile->getLight());
            }
            if (ImGui::Button("Change Handler"))
                selected_light_ = road_tile->getLight();
        }
        ImGui::End();
    }
}

void MapBuilder::addRoad(const sf::Vector2f &pos, TileType type)
{
    auto tile = map_.grid_.getTile(pos);
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
    if (tile->getType() != Empty)
    {
        RoadTile *temp = static_cast<RoadTile *>(tile);
        if (temp->getLight())
        {
            map_.removeLight(temp->getLight());
            temp->removeLight();
        }
    }
    RoadTile *r = static_cast<RoadTile *>(road_tile.get());
    auto arr = map_.grid_.getNeigborTiles(tile->getTileIndex());
    r->autoRotate(arr);

    map_.grid_.swapTile(road_tile);
    connectRoads();
}

void MapBuilder::slideAdd(const sf::Vector2f &pos)
{
    selected_tile_index_ = UINT_MAX;
    if (hovered_tile_index_ == last_tile_index_)
        return;
    if (last_tile_index_ != UINT_MAX)
    {
        if (!map_.grid_.getTile(hovered_tile_index_) || map_.grid_.getTile(hovered_tile_index_)->getType() != Empty)
            return;
        auto last_tile = map_.grid_.getTile(last_tile_index_);
        if (last_tile && last_tile->getType() != Empty)
        {
            auto last_road = static_cast<RoadTile *>(last_tile);
            auto neighbors = map_.grid_.getNeigborTiles(last_tile_index_);
            if (last_road->getDir().x == 1)
            {
                if (neighbors[RIGHT] && neighbors[RIGHT]->getTileIndex() != hovered_tile_index_)
                {
                    addRoad(last_tile->getCenter(), RoadTurnType);
                    if (last_tile_index_ - hovered_tile_index_ == map_.grid_.getSideCount())
                    {
                        auto new_road = static_cast<RoadTile *>(map_.grid_.getTile(last_tile_index_));
                        new_road->flip();
                    }
                }
            }
            else if (last_road->getDir().x == -1)
            {
                if (neighbors[LEFT] && neighbors[LEFT]->getTileIndex() != hovered_tile_index_)
                {
                    addRoad(last_tile->getCenter(), RoadTurnType);
                    if (hovered_tile_index_ - last_tile_index_ == map_.grid_.getSideCount())
                    {
                        auto new_road = static_cast<RoadTile *>(map_.grid_.getTile(last_tile_index_));
                        new_road->flip();
                    }
                }
            }
            else if (last_road->getDir().y == 1)
            {
                if (neighbors[UP] && neighbors[UP]->getTileIndex() != hovered_tile_index_)
                {
                    addRoad(last_tile->getCenter(), RoadTurnType);
                    if (last_tile_index_ - hovered_tile_index_ == 1)
                    {
                        auto new_road = static_cast<RoadTile *>(map_.grid_.getTile(last_tile_index_));
                        new_road->flip();
                    }
                }
            }
            else if (last_road->getDir().y == -1)
            {
                if (neighbors[DOWN] && neighbors[DOWN]->getTileIndex() != hovered_tile_index_)
                {
                    addRoad(last_tile->getCenter(), RoadTurnType);
                    if (hovered_tile_index_ - last_tile_index_ == 1)
                    {
                        auto new_road = static_cast<RoadTile *>(map_.grid_.getTile(last_tile_index_));
                        new_road->flip();
                    }
                }
            }
        }
    }
    addRoad(pos, StraightRoadType);
    last_tile_index_ = hovered_tile_index_;
}

void MapBuilder::addTrafficLight(const sf::Vector2f &pos)
{
    auto tile = map_.grid_.getTile(pos);
    if (!tile || tile->getType() != StraightRoadType)
        return;

    RoadTile *road = static_cast<RoadTile *>(tile);
    if (road->getLight())
        return;
    road->addLight(map_.getCurrentHandlerId());
    map_.addLight(road->getLight());
}

void MapBuilder::removeRoad(const sf::Vector2f &pos)
{
    auto tile = map_.grid_.getTile(pos);
    if (!tile || tile->getType() == TileType::Empty)
        return;
    RoadTile *road = static_cast<RoadTile *>(tile);
    if (road->getLight())
    {
        map_.removeLight(road->getLight());
    }
    std::unique_ptr<Tile> empty_tile = std::make_unique<Tile>(tile->getPos(), tile->getSize(), tile->getTileIndex());
    map_.grid_.swapTile(empty_tile);
    connectRoads();
}
void MapBuilder::rotateRoad(const sf::Vector2f &pos)
{
    auto tile = map_.grid_.getTile(pos);
    if (!tile || tile->getType() == TileType::Empty)
        return;

    RoadTile *road_tile = static_cast<RoadTile *>(tile);
    road_tile->rotate();
    connectRoads();
}

void MapBuilder::flipRoad(const sf::Vector2f &pos)
{
    auto tile = map_.grid_.getTile(pos);
    if (!tile || tile->getType() == TileType::Empty)
        return;

    RoadTile *road_tile = static_cast<RoadTile *>(tile);
    road_tile->flip();
    connectRoads();
}

void MapBuilder::connectRoad(Tile *tile)
{
    // TODO - Do we need to disconnect empty tiles when clearing?
    if (tile && tile->getType() != TileType::Empty)
    {
        tile->getNode()->disconnectAll();
        RoadTile *road_tile = static_cast<RoadTile *>(tile);
        auto arr = map_.grid_.getNeigborTiles(tile->getTileIndex());
        road_tile->connect(arr);
    }
}

void MapBuilder::connectRoads()
{
    for (unsigned int i = 0; i < map_.grid_.getTotalTileCount(); ++i)
    {
        auto tile = map_.grid_.getTile(i);
        connectRoad(tile);
    }
}

void MapBuilder::changeLightHandler(const sf::Vector2f &pos)
{
    auto tile = map_.grid_.getTile(pos);
    if (!tile || tile->getType() == TileType::Empty)
        return;
    RoadTile *new_light_tile = static_cast<RoadTile *>(tile);
    TrafficLight *new_light = new_light_tile->getLight();
    if (new_light_tile->getLight())
    {
        map_.removeLight(selected_light_);
        selected_light_->setHandlerId(new_light->getHandlerId());
        map_.addLight(selected_light_, new_light->getHandlerId());
    }
    selected_light_ = nullptr;
}

void MapBuilder::clearMap()
{
    map_.grid_.init();
    connectRoads();
}
/*
*   Builder input
*/

void MapBuilder::selectTile(const sf::Vector2f &pos)
{
    auto new_tile = map_.grid_.getTile(pos);
    if (!new_tile)
    {
        unSelectTile();
        return;
    }
    if (new_tile->getTileIndex() == selected_tile_index_)
    {
        new_tile->unSelectTile();
        selected_tile_index_ = UINT_MAX;
    }
    else
    {
        new_tile->selectTile();
        unSelectTile();
        selected_tile_index_ = new_tile->getTileIndex();
        select_menu_pos_ = window_.convert(new_tile->getPos() + sf::Vector2f(new_tile->getSize(), 0.f));
    }
}

void MapBuilder::unSelectTile()
{
    if (selected_tile_index_ != UINT_MAX)
        map_.grid_.getTile(selected_tile_index_)->unSelectTile();
    selected_tile_index_ = UINT_MAX;
}

void MapBuilder::setBuildingMode(bool val)
{
    if (building_mode_ == val)
        return;
    building_mode_ = val;
    editing_option_ = Inspect;
    road_option_ = TileType::StraightRoadType;
    selected_tile_index_ = UINT_MAX;
    hovered_tile_index_ = UINT_MAX;
    selected_light_ = nullptr;
}

void MapBuilder::handleInput(const sf::Event &ev)
{
    if (ev.type == sf::Event::MouseButtonPressed)
    {
        if (window_.isGuiHovered())
            return;
        sf::Vector2f pos = window_.convert(sf::Vector2i(ev.mouseButton.x, ev.mouseButton.y));
        if (ev.mouseButton.button == sf::Mouse::Right)
        {
            if (selected_light_)
            {
                changeLightHandler(pos);
            }
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
        auto new_tile = map_.grid_.getTile(pos);
        if (!new_tile)
            return;
        if (selected_tile_index_ != new_tile->getTileIndex())
        {
            if (hovered_tile_index_ != UINT_MAX)
                if (hovered_tile_index_ != selected_tile_index_)
                    map_.grid_.getTile(hovered_tile_index_)->unSelectTile();
            new_tile->hoverTile();
            hovered_tile_index_ = new_tile->getTileIndex();
        }
    }
    else if(ev.type == sf::Event::MouseButtonReleased)
    {
        last_tile_index_ = UINT_MAX;
    }
}

} // namespace TrafficSim