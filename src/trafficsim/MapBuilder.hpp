#pragma once

#include <climits> // UINT_MAX

#include "Map.hpp"
#include "RoadTurn.hpp"
#include "StraightRoad.hpp"
#include "RoadIntersection.hpp"
#include "RoadTrisection.hpp"
#include "RoadJunction.hpp"
#include "TrafficLight.hpp"
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

    void setBuildingMode(bool val);

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
    EditingOption editing_option_ = Inspect;
    TileType road_option_ = TileType::StraightRoadType;
    unsigned int selected_tile_index = UINT_MAX;
    unsigned int hovered_tile_index = UINT_MAX;
    TrafficLight *selected_light_ = nullptr;
    sf::Vector2i select_menu_pos_;

private:
    void removeRoad(const sf::Vector2f &pos);
    void selectTile(const sf::Vector2f &pos);
    void unSelectTile();
    void connectRoad(std::unique_ptr<Tile> &tile);
    void connectRoads();
    void changeLightHandler(const sf::Vector2f &pos);
};
} // namespace TrafficSim