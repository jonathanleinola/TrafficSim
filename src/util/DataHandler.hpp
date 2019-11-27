#pragma once

#include <SFML/Graphics.hpp>
#include "trafficsim/MapBuilder.hpp"

#include <map>
#include <memory>
#include <string>
#include <utility>

namespace TrafficSim
{

class DataHandler
{

public:
    DataHandler(){};
    // Loads texture from file
    void loadTexture(const char *src, const char *texture_key);
    void loadTexturesFromFile(const char *src);

    void loadMap(const char *file_name, MapBuilder &builder) const;
    void saveMap(const char *file_name, Grid &grid) const;

    const sf::Texture *getTexture(const char *texture_name) { return textures_[texture_name].get(); }

private:
    std::map<std::string, std::unique_ptr<sf::Texture>> textures_;
};

} // namespace TrafficSim
