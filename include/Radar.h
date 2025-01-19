#ifndef RADAR_H
#define RADAR_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Object.h"

class Radar {
public:
    Radar(sf::Vector2f position, float radius);

    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    void scan(const std::vector<Object>& objects);

private:
    sf::Vector2f position;
    float radius;
    float scanAngle;

    sf::CircleShape radarPoint;
    sf::RectangleShape radarLine;
};
#endif
