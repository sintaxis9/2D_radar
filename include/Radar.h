#ifndef RADAR_H
#define RADAR_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Object.h"
#include "Grid.h"
#include "SFML/Graphics/CircleShape.hpp"

class Radar {
public:
    Radar(sf::Vector2f position, float radius);

    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    void scan(const std::vector<Object>& objects);
    void drawDetectionGrid(sf::RenderWindow& window);

private:
    sf::Vector2f position;
    float radius;
    float scanAngle;

    sf::CircleShape radarPoint;
    sf::CircleShape detectionArea;
    sf::RectangleShape radarLine;
    Grid detectionGrid;

    bool isDetecting;
    float blinkTimer;
};

#endif
