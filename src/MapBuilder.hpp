#pragma once

#include <climits> // UINT_MAX

#include "imgui.h"
#include "imgui-SFML.h"
#include "imgui_internal.h"

#include "Grid.hpp"
#include "RoadTurn.hpp"
#include "StraightRoad.hpp"
#include "RoadIntersection.hpp"
#include "RoadTrisection.hpp"
#include "RoadJunction.hpp"

namespace TrafficSim
{

enum EditingOption
{
    Select = 0,
    Add,
    Remove,
    Rotate,
    Flip,

    // Keep this as last
    ModeCount
};

class MapBuilder
{
public:
    MapBuilder(Grid &grid);

    void toggle_building_mode() { building_mode_ = !building_mode_; }
    void handleInput(const sf::Event &ev);
    void drawGUI();

private:
    bool building_mode_ = true;
    bool gui_hovered = false;
    Grid &grid_;
    EditingOption editing_option_ = EditingOption::Select;
    TileType road_option_ = TileType::StraightRoadType;
    unsigned int selected_tile_index = UINT_MAX;

private:
    void addRoad(const sf::Vector2f &pos, TileType type);
    void removeRoad(const sf::Vector2f &pos);
    void flipRoad(const sf::Vector2f &pos);
    void selectTile(const sf::Vector2f &pos);
    void rotateRoad(const sf::Vector2f &pos);
    void connectRoad(std::unique_ptr<Tile> &tile);
    void connectRoads();
};
} // namespace TrafficSim