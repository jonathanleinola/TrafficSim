#pragma once

#include <SFML/Graphics.hpp>


namespace TrafficSim
{

enum LightColor
{
    RED = 0,
    YELLOW,
    GREEN
};

class TrafficLight : public sf::Drawable
{
public:
    TrafficLight(const sf::Vector2f &pos, const sf::Vector2f &dir, float tile_size, unsigned int handler_id);

    bool isActivated() const { return activated_; }
    unsigned int getHandlerId() const { return handler_id_; }

    void update(float delta_time);

    void setHandlerId(unsigned int id) { handler_id_ = id; }
    void initPos(const sf::Vector2f &pos, const sf::Vector2f &dir, float tile_size);
    void activate();

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    // This stores in which handler does this light belongs to, can be changed in run time
    unsigned int handler_id_;
    sf::Vector2f pos_;
    sf::RectangleShape shape_;
    LightColor color_ = RED;
    bool activated_ = false;

    // For how long each light will be activated
    float green_time_ = 5;
    float yellow_time_ = 1;
    // time in seconds from lights activation
    float activated_for_ = 0;

    void deActivate();
    void setColor(LightColor color);
};

} // namespace TrafficSim
