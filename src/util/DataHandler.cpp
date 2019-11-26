#include "DataHandler.hpp"
#include <iostream>
#include <fstream>

namespace TrafficSim
{

void DataHandler::loadTexture(const char *src, const char *texture_key)
{
    textures_.insert(std::make_pair(texture_key, std::make_unique<sf::Texture>()));
    textures_[texture_key]->loadFromFile(src);
}

void DataHandler::loadMap(const char *file_name, MapBuilder &builder) const
{
    builder.clearMap();
    /*
    *   Load map using methods from MapBuilder:
    *   builder.addRoad(), builder.rotateRoad() and .flipRoad()
    * 
    */
}

void DataHandler::saveMap(const char *file_name, Grid &grid) const
{

    /*
    *   Use XML or JSON
    *   
    *   Tiles are stored in grid, to access tile you can use grid.getTile(index) ( returns unique_ptr to Tile )
    * 
    *   Indexes go from 0 to grid.getSize()
    * 
    *   To get type of Tile use tile.getType() enum value of TileType
    * 
    *   If tile is not of type Empty convert it with static_cast to RoadTile*
    *   this will allow to get access to getDir() and isFlipped() functions
    *   RoadTile *road = static_cast<RoadTile *>(tile.get());
    * 
    *   to get the position of road use .getPos()
    */
    //if(grid.getTile(0)==NULL)
    //    return 0;
    std::cout << "Save map" << std::endl;
    FILE * fp=fopen(file_name,"w");
    //if(!fp)
    //    return 0;

    for(unsigned int i=0;i<grid.getSideCount()*grid.getSideCount();i++)
    {   

        //std::cout << pos.x <<" "<< pos.y << std::endl;
        if(grid.getTile(i)->getType()!=5)
        {
            
            RoadTile *road = static_cast<RoadTile *>(grid.getTile(i));
            fprintf(fp, "%d,{%f %f},{%f %f}\n", road->getType(),road->getDir().x,road->getDir().y,road->getPos().x,road->getPos().y);
        }
        else
        {

        }
            
            
    }
    

    fclose(fp);
    std::cout << "Map Saved" << std::endl;
   
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

            auto texture_key = line.substr(0, line.find(" "));
            auto file_name = line.substr(line.find(" ") + 1);

            loadTexture(file_name.c_str(), texture_key.c_str());
        }
    }
    else
    {
        std::cout << "File: " << src << " not found." << std::endl;
    }
}

} // namespace TrafficSim