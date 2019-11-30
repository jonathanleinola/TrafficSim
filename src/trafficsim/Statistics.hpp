#pragma once

#include <climits> // UINT_MAX

#include <SFML/Graphics.hpp>

#include "core/Window.hpp"
#include "Map.hpp"

namespace TrafficSim
{
class Statistics
{
public:
  Statistics(Map &map, const Window &window);

  // Handle mouse input to select the map
  void handleInput(const sf::Event &ev);

  void drawGUI();

private:
  Map &map_;
  const Window &window_;
  // Stores highlighted tile, which was left clicked
  unsigned int selected_tile_index_ = UINT_MAX;
  void selectTile(const sf::Vector2f &pos);
  void unSelectTile();
};
} // namespace TrafficSim