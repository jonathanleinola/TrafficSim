#pragma once

#include <SFML/Graphics.hpp>

namespace TrafficSim
{
    
class DataHandler
{

public:
    // Loads texture from file
    static bool LoadTexture(const char *src, sf::Texture &texture_dest);

};

} // namespace TrafficSim
