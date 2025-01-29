#ifndef RADAR_H
#define RADAR_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>
#include "Object.h"
#include "Grid.h"

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
    bool isDetecting;
    float blinkTimer;

    sf::CircleShape radarPoint;
    sf::CircleShape detectionArea;
    sf::RectangleShape radarLine;
    Grid detectionGrid;

    std::unordered_map<std::string, float> detectionCooldowns;
};

#endif
