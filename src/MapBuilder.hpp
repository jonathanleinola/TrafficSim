#pragma once

#include <climits> // UINT_MAX

#include "imgui.h"
#include "imgui-SFML.h"
#include "imgui_internal.h"

#include "Grid.hpp"
#include "RoadTile.hpp"


namespace TrafficSim
{

enum EditingMode
{
    Select, Add, Remove, Rotate
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
    Grid &grid_;
    EditingMode editing_mode_ = EditingMode::Select;
    unsigned int selected_tile_ = UINT_MAX;

private:
    void addRoad(const sf::Vector2f &pos);
    void removeRoad(const sf::Vector2f &pos);
    void selectTile(const sf::Vector2f &pos);
    void rotateRoad(const sf::Vector2f &pos);
};
} // namespace TrafficSim