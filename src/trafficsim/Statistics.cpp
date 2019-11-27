#include "Statistics.hpp"

#include <iostream>
#include <string>

#include "imgui.h"
#include "imgui-SFML.h"
#include "imgui_internal.h"

namespace TrafficSim
{
Statistics::Statistics(Map &map, const Window &window) : map_(map), window_(window){};

void Statistics::drawGUI()
{
    if (selected_tile_index_ != UINT_MAX && map_.grid_.getTile(selected_tile_index_)->getCategory() == RoadCategory)
    {
        const auto &node_data = map_.grid_.getTile(selected_tile_index_)->getNode()->getCarsPassed().data();
        std::size_t data_size = map_.grid_.getTile(selected_tile_index_)->getNode()->getCarsPassed().size();

        constexpr float SCALE_MAX = 300.f;
        constexpr float SCALE_MIN = 0.f;

        // Getter to convert std::uin16_t array to float array
        static auto getter = [](void *data, int idx) -> float {
            std::uint16_t *values = (std::uint16_t *)(data);
            return (float)(values[idx]);
        };

        ImGui::Begin("Statistics");
        int x = ImGui::GetContentRegionAvail().x;
        int y = ImGui::GetContentRegionAvail().y / 2;
        ImGui::PlotLines("Frame Times", getter, (void *)node_data, data_size, 0, "Number of Vehicles", SCALE_MIN, SCALE_MAX, ImVec2(x, y));
        ImGui::PlotHistogram("Histogram", getter, (void *)node_data, data_size, 0, "Number of Vehicles", SCALE_MIN, SCALE_MAX, ImVec2(x, y));
        ImGui::End();
    }

    //static float TestData[6] = {0.f, 4.f, 3.f, 2.f, 0.f, 4.f};
    //ImGui::PlotHistogram("Histogram Test", TestData, 6, 0, "Test", 0.f, 5.f, ImVec2(0, 80));
    //   static float arr[] = {0.6f, 0.1f, 1.0f, 0.5f, 0.92f, 0.1f, 0.2f};
    //   std::vector<float> v = {0.6f, 0.1f, 1.0f, 0.5f, 0.92f, 0.1f, 0.2f};
}

void Statistics::selectTile(const sf::Vector2f &pos)
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
    }
}

void Statistics::unSelectTile()
{
    if (selected_tile_index_ != UINT_MAX)
        map_.grid_.getTile(selected_tile_index_)->unSelectTile();
    selected_tile_index_ = UINT_MAX;
}

void Statistics::handleInput(const sf::Event &ev)
{
    if (ev.type == sf::Event::MouseButtonPressed)
    {
        if (window_.isGuiHovered())
            return;
        sf::Vector2f pos = window_.convert(sf::Vector2i(ev.mouseButton.x, ev.mouseButton.y));
        if (ev.mouseButton.button == sf::Mouse::Right)
        {
            unSelectTile();
        }
        else if (ev.mouseButton.button == sf::Mouse::Left)
        {
            selectTile(pos);
        }
    }
}

} // namespace TrafficSim