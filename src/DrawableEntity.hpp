#pragma once

#include <SFML/Graphics.hpp>

#include "Window.hpp"

/*

    Base class for Road, Building, Car etc
    In deriveds' classes' constructor make std::vector which will contain sf::Vertex
    verticies' position you can get from Nodes

*/

namespace TrafficSim
{
    
class DrawableEntity : public sf::Drawable
{
public:
    DrawableEntity();
    virtual void draw(Window &window) const;
protected:
    // This function is inherited from sf::Drawable
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    //These will be drawn to the screen
    std::vector<sf::Vertex> vertices_;
private:
};

} // namespace TrafficSim
