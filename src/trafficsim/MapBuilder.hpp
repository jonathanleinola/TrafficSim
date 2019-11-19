#pragma once

#include <climits> // UINT_MAX

#include "imgui.h"
#include "imgui-SFML.h"
#include "imgui_internal.h"

#include "Map.hpp"
#include "RoadTurn.hpp"
#include "StraightRoad.hpp"
#include "RoadIntersection.hpp"
#include "RoadTrisection.hpp"
#include "RoadJunction.hpp"
#include "core/Window.hpp"

namespace TrafficSim
{

enum EditingOption
{
    Inspect = 0,
    AddRoad,
    Remove,
    Rotate,
    Flip,
    AddLight,

    // Keep this as last
    ModeCount
};

class MapBuilder
{
public:
    MapBuilder(Map &map, const Window &window);

    void toggle_building_mode() { building_mode_ = !building_mode_; }
    void handleInput(const sf::Event &ev);
    void drawGUI();

    void clearMap();

    // Adds a road
    void addRoad(const sf::Vector2f &pos, TileType type);
    // Rotates roads 90 degrees clockwise
    void rotateRoad(const sf::Vector2f &pos);
    //Rotates flips roads
    void flipRoad(const sf::Vector2f &pos);
    void addTrafficLight(const sf::Vector2f &pos);

private:
    Map &map_;
    const Window &window_;
    bool building_mode_ = true;
    bool gui_hovered = false;
    EditingOption editing_option_ = Inspect;
    TileType road_option_ = TileType::StraightRoadType;
    unsigned int selected_tile_index = UINT_MAX;
    unsigned int hovered_tile_index = UINT_MAX;
    sf::Vector2i select_menu_pos_;

private:
    void removeRoad(const sf::Vector2f &pos);
    void selectTile(const sf::Vector2f &pos);
    void unSelectTile();
    void connectRoad(std::unique_ptr<Tile> &tile);
    void connectRoads();
};
} // namespace TrafficSim