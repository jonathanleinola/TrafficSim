#include "DataHandler.hpp"
#include "CsvRow.hpp"
#include <fstream>
#include <string>   // std::string
#include <iostream> // std::cout
#include <sstream>  // std::istringstream

namespace TrafficSim
{

void DataHandler::loadTexture(const char *src, const char *texture_key)
{
    textures_.insert(std::make_pair(texture_key, std::make_unique<sf::Texture>()));
    textures_[texture_key]->loadFromFile(src);
}

void DataHandler::loadMap(const char *file_name, MapBuilder &builder, Grid &grid) const
{
    builder.clearMap();

    std::ifstream file("test.csv");
    sf::Vector2f pos, dir;
    int i,j,flipped;

    CsvRow row;
    while (file >> row)
    {
        //std::cout << row[0] << row[1] << row[2] << row[3] << row[4] << "\n";

        i = stoi(row[0]);
        j=stoi(row[1]);
        TileCategory tile_category = static_cast<TileCategory>(i);
        RoadType road_type = static_cast<RoadType>(j);
        

        if (tile_category == TileCategory::RoadCategory)
        {

            pos.x = stof(row[4]);
            pos.y = stof(row[5]);

            dir.x = stoi(row[2]);
            dir.y = stoi(row[3]);

            flipped=stoi(row[6]);

            //add road
            // Fix the middle zero
            // you need to save road type. 
            //    StraightRoadType = 0,
            
            if(road_type==RoadType::StraightRoadType)
            {
                builder.addRoad(pos, RoadType::StraightRoadType, false);
            }
            else if(road_type==RoadType::RoadTurnType)
            {
                builder.addRoad(pos, RoadType::RoadTurnType, false);
            
            }
            else if(road_type==RoadType::HomeRoadType)
            {
                builder.addRoad(pos, RoadType::HomeRoadType, false);
            }
            else if(road_type==RoadType::IntersectionType)
            {
                builder.addRoad(pos, RoadType::IntersectionType, false);
            }
            else if(road_type==RoadType::JunctionType){
                builder.addRoad(pos, RoadType::JunctionType, false);
            }
            else if(road_type==RoadType::TrisectionType)
            {
                builder.addRoad(pos, RoadType::TrisectionType, false);
            }
            

                
            // Direction of the road
            // Up: { 0, 1 }, Right { 1, 0 }, Down { 0, -1 }, Left { -1, 0 }

            //std::cout << dir.x << " " << dir.y << std::endl;
            if(flipped==0)
                builder.flipRoad(pos);
            
            if (dir.x == 0 && dir.y == -1 && flipped==1)
            {
                builder.rotateRoad(pos);
            }
            else if (dir.x == -1 && dir.y == 0 && flipped==1)
            {
                builder.rotateRoad(pos);
                builder.rotateRoad(pos);
            }
            else if (dir.x == 0 && dir.y == 1 && flipped==1)
            {
                builder.rotateRoad(pos);
                builder.rotateRoad(pos);
                builder.rotateRoad(pos);
            }
            
        }
        
    }

    /*
    *   Load map using methods from MapBuilder:
    *   builder.addRoad(), builder.rotateRoad() and .flipRoad()
    * 

   std::cout << "Load map" << std::endl;
   FILE * fp=fopen(file_name,"r");
   while (getline(fp, ID, ',')) {
    cout << "ID: " << ID << " " ; 

    getline(file, nome, ',') ;
    cout << "User: " << nome << " " ;

    getline(file, idade, ',') ;
    cout << "Idade: " << idade << " "  ; 

    getline(file, genero);
    cout << "Sexo: " <<  genero<< " "  ;
} 
    
    
    for(unsigned int i=0;i<grid.getSideCount()*grid.getSideCount();i++)
    {
            //std::cout << pos.x <<" "<< pos.y << std::endl;
        if(grid.getTile(i)->getType()== TileType::Empty)
        {
            
            RoadTile *road = static_cast<RoadTile *>(grid.getTile(i));
            fprintf(fp, "%d,{%f %f},{%f %f}\n", road->getType(),road->getDir().x,road->getDir().y,road->getPos().x,road->getPos().y);
        }
        else
        {

        }
    }
    
   fclose(fp);
   */
    std::cout << "Map Loaded" << std::endl;
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
    FILE *fp = fopen(file_name, "w");
    //if(!fp)
    //    return 0;

    // TODO save left and right turns and dtraffic lights
    for (unsigned int i = 0; i < grid.getSideCount() * grid.getSideCount(); i++)
    {

        //std::cout << pos.x <<" "<< pos.y << std::endl;
        if (grid.getTile(i)->getCategory() == TileCategory::RoadCategory)
        {
            
            RoadTile *road = static_cast<RoadTile *>(grid.getTile(i));
            if(road->getLight())
            {
                fprintf(fp, "%d,%d,%f,%f,%f,%f,%d,%f,%f,%d\n", road->getCategory(),road->getType(), road->getDir().x, road->getDir().y, road->getPos().x, road->getPos().y,road->isFlipped(),road->getLight()->getPos().x,road->getLight()->getPos().y,road->getLight()->getHandlerId());
            }
            else
            {
                fprintf(fp, "%d,%d,%f,%f,%f,%f,%d\n", road->getCategory(),road->getType(), road->getDir().x, road->getDir().y, road->getPos().x, road->getPos().y,road->isFlipped());
            }
            
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