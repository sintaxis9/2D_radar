#include "../include/Radar.h"
#include <iostream>
#include <cmath>

Radar::Radar(sf::Vector2f position, float radius)
    : position(position), radius(radius), scanAngle(0) {
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

    for (auto& detection : detections) {
        detection.timer -= deltaTime;
    }

    detections.erase(
        std::remove_if(detections.begin(), detections.end(),
                       [](const Detection& d) { return d.timer <= 0; }),
        detections.end());
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
                // Guardar la detección
                detections.push_back({ objPosition, 1.0f });  // El punto se desvanece en 1 segundo
            }
        }
    }
}

void Radar::drawDetectionGrid(sf::RenderWindow& window) {
    const int gridSize = 20;
    const int gridWidth = 400;
    const int gridHeight = 600;
    const sf::Vector2f gridPosition(800, 0);

    sf::RectangleShape line(sf::Vector2f(gridWidth, 1));
    line.setFillColor(sf::Color(50, 255, 50));
    for (int y = 0; y <= gridHeight; y += gridSize) {
        line.setSize(sf::Vector2f(gridWidth, 1));
        line.setPosition(gridPosition.x, gridPosition.y + y);
        window.draw(line);
    }

    line.setSize(sf::Vector2f(1, gridHeight));
    for (int x = 0; x <= gridWidth; x += gridSize) {
        line.setPosition(gridPosition.x + x, gridPosition.y);
        window.draw(line);
    }

    for (const auto& detection : detections) {
        sf::CircleShape detectionPoint(5);
        detectionPoint.setFillColor(sf::Color(255, 0, 0, static_cast<sf::Uint8>(detection.timer * 255)));
        detectionPoint.setOrigin(5, 5);

        sf::Vector2f relativePosition = detection.position - position;
        relativePosition *= (gridWidth / (2 * radius));
        relativePosition += sf::Vector2f(gridWidth / 2, gridHeight / 2);

        detectionPoint.setPosition(gridPosition + relativePosition);
        window.draw(detectionPoint);
    }
}
