#ifndef GRID_H
#define GRID_H

#include <SFML/Graphics.hpp>
#include <vector>

struct Detection {
    sf::Vector2f position;
    float timer;
};

class Grid {
public:
    Grid(sf::Vector2f position, sf::Vector2f size, int cellSize);

    void addDetection(sf::Vector2f position, float lifetime);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);

private:
    sf::Vector2f position;
    sf::Vector2f size;
    int cellSize;
    std::vector<Detection> detections;
};

#endif
