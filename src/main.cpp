#include <iostream>
#include <vector>

#include "SFML/Graphics.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Traffic simulator");
    sf::RectangleShape rect(sf::Vector2f(100, 100));
    rect.setOrigin(50, 50);
    rect.setPosition(1280/2, 720/2);


    sf::Vertex point(sf::Vector2f(10, 10));
    point.color = sf::Color::Red;
    sf::Vertex point2(sf::Vector2f(600, 500));
    point2.color = sf::Color::Blue;
    std::vector<sf::Vertex> points;
    points.push_back(point);
    points.push_back(point2);
    

    while (window.isOpen())
    {
        sf::Event Event;
        while (window.pollEvent(Event))
        {
            if (Event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(rect);
        window.draw(&points[0], points.size(), sf::Lines);
        window.display();
    }
    std::cout << "Hello, Traffic sim!"<< "\n";
}