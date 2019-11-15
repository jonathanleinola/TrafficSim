#include "DataHandler.hpp"

#include <iostream>

#include <sstream>
#include <fstream>

namespace TrafficSim
{

bool DataHandler::LoadTexture(const char *src, sf::Texture &texture_dest)
{
    if (!texture_dest.loadFromFile(src))
    {
        std::cout << "Could not load texture: " << src << std::endl;
        return false;
    }
    else
    {
        std::cout << "Texture loaded." << std::endl;
        return true;
    }
}

bool DataHandler::LoadTexturesFromFile(const char *src, std::map<std::string, std::unique_ptr<sf::Texture>> &dest)
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
            dest.insert(std::make_pair(texture_key, std::make_unique<sf::Texture>()));
            if (!DataHandler::LoadTexture(file_name.c_str(), *dest[texture_key]))
                return false;
        }
        return true;
    }
    else
    {
        std::cout << "File: " << src << " not found." << std::endl;
        return false;
    }
}

} // namespace TrafficSim