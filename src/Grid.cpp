#include "../include/Grid.h"
#include "SFML/System/Vector2.hpp"
#include <cmath>

Grid::Grid(sf::Vector2f position, sf::Vector2f size, int cellSize)
    : position(position), size(size), cellSize(cellSize) {}

void Grid::addDetection(sf::Vector2f position, float lifetime) {
    const float minDistance = 10.0f;
    for (const auto& detection : detections){
        sf:sf::Vector2f delta = detection.position - position;
        float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y);
        if (distance < minDistance){
            return;
        }
    }
    detections.push_back({position, lifetime});
}

void Grid::update(float deltaTime) {
    for (auto it = detections.begin(); it != detections.end();) {
        it->timer -= deltaTime;
        if (it->timer <= 0) {
            it = detections.erase(it);
        } else {
            ++it;
        }
    }
}

void Grid::draw(sf::RenderWindow& window) {
    sf::RectangleShape line;

    line.setSize(sf::Vector2f(size.x, 1));
    line.setFillColor(sf::Color(50, 255, 50, 100));
    for (int y = 0; y <= size.y; y += cellSize) {
        line.setPosition(position.x, position.y + y);
        window.draw(line);
    }

    line.setSize(sf::Vector2f(1, size.y));
    for (int x = 0; x <= size.x; x += cellSize) {
        line.setPosition(position.x + x, position.y);
        window.draw(line);
    }

    for (const auto& detection : detections) {
        sf::CircleShape detectionPoint(5);
        detectionPoint.setFillColor(sf::Color(255, 0, 0, static_cast<sf::Uint8>(detection.timer * 255)));
        detectionPoint.setOrigin(5, 5);

        sf::Vector2f relativePosition = detection.position;
        relativePosition += sf::Vector2f(size.x / 2, size.y / 2);
        detectionPoint.setPosition(position + relativePosition);
        window.draw(detectionPoint);
    }
}
