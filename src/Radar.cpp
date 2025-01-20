#include "../include/Radar.h"
#include <iostream>
#include <cmath>

Radar::Radar(sf::Vector2f position, float radius)
    : position(position), radius(radius), scanAngle(0),
      detectionGrid(sf::Vector2f(800, 0), sf::Vector2f(400, 600), 20) {

    radarPoint.setRadius(5);
    radarPoint.setFillColor(sf::Color::Red);
    radarPoint.setOrigin(5, 5);
    radarPoint.setPosition(position);

    radarLine.setSize(sf::Vector2f(radius, 2.0f));
    radarLine.setOrigin(0, 1);
    radarLine.setPosition(position);
    radarLine.setFillColor(sf::Color::Green);
}

void Radar::update(float deltaTime) {
    scanAngle += 90.0f * deltaTime;
    if (scanAngle >= 360.0f) {
        scanAngle -= 360.0f;
    }
    radarLine.setRotation(scanAngle);
    detectionGrid.update(deltaTime);
}

void Radar::draw(sf::RenderWindow& window) {
    window.draw(radarPoint);
    window.draw(radarLine);
}

void Radar::scan(const std::vector<Object>& objects) {
    for (const auto& obj : objects) {
        float rayAngle = scanAngle * M_PI / 180.0f;

        sf::Vector2f objPosition = obj.getPosition();
        float dx = objPosition.x - position.x;
        float dy = objPosition.y - position.y;
        float distance = std::sqrt(dx * dx + dy * dy);

        if (distance <= radius) {
            float angleToObj = std::atan2(dy, dx);
            float angleDifference = std::fmod(angleToObj - rayAngle, 2 * M_PI);

            if (std::abs(angleDifference) < 0.1f) {
                detectionGrid.addDetection(objPosition - position, 1.0f); // Agregar detección
                std::cout << "colision detectada a " << distance << " unidades" << std::endl;
            }
        }
    }
}
void Radar::drawDetectionGrid(sf::RenderWindow& window) {
    detectionGrid.draw(window);
}
