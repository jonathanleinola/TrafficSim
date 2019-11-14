#pragma once

#include <climits> // UINT_MAX

#include "imgui.h"
#include "imgui-SFML.h"
#include "imgui_internal.h"

#include "Grid.hpp"
#include "RoadTile.hpp"
#include "RoadTurn.hpp"
#include "StraightRoad.hpp"
#include "RoadIntersection.hpp"
#include "RoadTrisection.hpp"

namespace TrafficSim
{

enum EditingMode
{
    Select,
    Add,
    Remove,
    Rotate,
    Flip
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
    EditingMode editing_mode_ = EditingMode::Select;
    TileType selected_road_ = TileType::StraightRoadType;
    unsigned int selected_tile_ = UINT_MAX;

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