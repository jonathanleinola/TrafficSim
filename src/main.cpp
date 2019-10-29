#include <iostream>

#include "SFML/Graphics.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Traffic simulator");
    sf::CircleShape circle(40);

    while (window.isOpen())
    {
        sf::Event Event;
        while (window.pollEvent(Event))
        {
            if (Event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(circle);
        window.display();
    }
    std::cout << "Hello, Traffic sim!"
              << "\n";
}