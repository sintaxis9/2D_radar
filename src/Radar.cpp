#include "Radar.h"
#include <cmath>
#include <iostream>

Radar::Radar(sf::Vector2f position, float radius)
    : position(position), radius(radius), scanAngle(0.0f) {
    radarShape.setRadius(radius);
    radarShape.setFillColor(sf::Color(0, 255, 0, 100));
    radarShape.setPosition(position);
}

void Radar::update(float deltaTime) {
    scanAngle += 90.0f * deltaTime;
    if (scanAngle >= 360.0f) {
        scanAngle -= 360.0f;
    }
}

void Radar::scan(const std::vector<Object>& objects) {
    for (const auto& obj : objects) {
        float distance = std::sqrt(std::pow(obj.getPosition().x - position.x, 2) +
                                   std::pow(obj.getPosition().y - position.y, 2));
        if (distance <= radius) {
            std::cout << "Objeto detectado: " << obj.getName() << " a " << distance << " unidades de distancia.\n";
        }
    }
}

void Radar::draw(sf::RenderWindow& window) {
    window.draw(radarShape);
}
