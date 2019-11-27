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
  std::vector<std::uint8_t> car_passed_total;
  if (selected_tile_index_ != UINT_MAX && map_.grid_.getTile(selected_tile_index_)->getType() != TileType::Empty)
  {
    car_passed_total = map_.grid_.getTile(selected_tile_index_)->getNode()->getCarsPassed();
    std::cout << +car_passed_total[0] << std::endl;
  }

  //static float TestData[6] = {0.f, 4.f, 3.f, 2.f, 0.f, 4.f};
  //ImGui::PlotHistogram("Histogram Test", TestData, 6, 0, "Test", 0.f, 5.f, ImVec2(0, 80));
  static float arr[] = {0.6f, 0.1f, 1.0f, 0.5f, 0.92f, 0.1f, 0.2f};
  std::vector<float> v = {0.6f, 0.1f, 1.0f, 0.5f, 0.92f, 0.1f, 0.2f};
  ImGui::Begin("Statistics");
  ImGui::PlotLines("Frame Times", arr, IM_ARRAYSIZE(arr));
  ImGui::PlotHistogram("Histogram", v.data(), IM_ARRAYSIZE(arr), 0, "Number of Vehicles", 0.0f, 5.0f, ImVec2(0, 100));
  ImGui::End();
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