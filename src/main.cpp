#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include "Radar.h"
#include "Object.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Radar 2D");

    Radar radar(sf::Vector2f(375, 275), 150);

    std::vector<Object> objects;
    objects.push_back(Object("Objeto 1", sf::Vector2f(400, 300), 20));
    objects.push_back(Object("Objeto 2", sf::Vector2f(500, 350), 20));
    objects.push_back(Object("Objeto 3", sf::Vector2f(300, 250), 20));
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Time deltaTime = clock.restart();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        radar.update(deltaTime.asSeconds());
        radar.scan(objects);
        window.clear();

        radar.draw(window);
        for (auto& obj : objects) {
            obj.draw(window);
        }

        window.display();
    }
    return 0;
}
