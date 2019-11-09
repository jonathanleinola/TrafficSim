#include "DataHandler.hpp"

#include <iostream>

namespace TrafficSim
{

bool DataHandler::LoadTexture(const char *src, sf::Texture &texture_dest)
{
    if (!texture_dest.loadFromFile(src))
    {
        std::cout << "Could not load texture: "<< src << std::endl;
        return true;
    }
    else
    {
        std::cout << "Texture loaded." << std::endl;
    }

    return false;
}

} // namespace TrafficSim