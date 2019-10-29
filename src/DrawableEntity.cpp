#include "DrawableEntity.hpp"

namespace TrafficSim
{

DrawableEntity::DrawableEntity()
{
}

void DrawableEntity::draw(Window &window) const
{
    window.draw(*this);
}

// This function is inherited from sf::Drawable
void DrawableEntity::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(&vertices_[0], vertices_.size(), sf::LineStrip, states);
}


} // namespace TrafficSim
