#pragma once

#include <SFML/Graphics.hpp>

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
    void loadTexture(const char *src);
    void loadTexturesFromFile(const char *src);

    const sf::Texture *getTextrue(const char *texture_name) { return textures_[texture_name].get(); }

private:
    std::map<std::string, std::unique_ptr<sf::Texture>> textures_;
};

} // namespace TrafficSim
