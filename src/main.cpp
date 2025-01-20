#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "../include/Radar.h"
#include "../include/Object.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1200, 600), "RADAR 2D");
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    Radar radar(sf::Vector2f(300, 300), 200);

    std::vector<Object> objects;
    for (int i = 0; i < 10; ++i) {
        sf::Vector2f randomPosition(
            std::rand() % 600,
            std::rand() % 600
        );
        float randomRadius = 10 + std::rand() % 20;
        objects.push_back(Object("objeto" + std::to_string(i + 1), randomPosition, randomRadius));
    }
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Time deltaTime = clock.restart();
        float elapsedTime = deltaTime.asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        radar.update(elapsedTime);
        radar.scan(objects);
        window.clear(sf::Color::Black);

        for (const auto& obj : objects) {
            sf::CircleShape objectShape(obj.getRadius());
            objectShape.setFillColor(sf::Color::White);
            objectShape.setPosition(obj.getPosition());
            window.draw(objectShape);
        }
        radar.draw(window);
        radar.drawDetectionGrid(window);
        window.display();
    }
    return 0;
}
