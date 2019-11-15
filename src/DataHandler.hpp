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
    // Loads texture from file
    static bool LoadTexture(const char *src, sf::Texture &texture_dest);
    static bool LoadTexturesFromFile(const char *src, std::map<std::string, std::unique_ptr<sf::Texture>> &dest);
};

} // namespace TrafficSim
