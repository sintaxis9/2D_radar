#ifndef RADAR_H
#define RADAR_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Object.h"

class Radar {
public:
    Radar(sf::Vector2f position, float radius);
    void update(float deltaTime);
    void scan(const std::vector<Object>& objects);
    void draw(sf::RenderWindow& window);

private:
    sf::Vector2f position;
    float radius;
    sf::CircleShape radarShape;
    float scanAngle;
};

#endif
