#include "DataHandler.hpp"

#include <iostream>

#include <sstream>
#include <fstream>

namespace TrafficSim
{

void DataHandler::loadTexture(const char *src)
{
}

void DataHandler::loadTexturesFromFile(const char *src)
{
    std::ifstream file(src);
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            if (line.size() < 3)
                continue;
            std::string texture_key = line.substr(0, line.find(" "));
            std::string file_name = line.substr(line.find(" ") + 1);
            textures_.insert(std::make_pair(texture_key, std::make_unique<sf::Texture>()));
            textures_[texture_key]->loadFromFile(file_name);
        }
    }
    else
    {
        std::cout << "File: " << src << " not found." << std::endl;
    }
}

} // namespace TrafficSim