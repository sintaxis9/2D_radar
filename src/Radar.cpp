#include "../include/Radar.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <unordered_map>

Radar::Radar(sf::Vector2f position, float radius)
    : position(position), radius(radius), scanAngle(0),
      isDetecting(false), blinkTimer(0.0f),
      detectionGrid(sf::Vector2f(800, 0), sf::Vector2f(400, 600), 20) {

    detectionArea.setRadius(radius);
    detectionArea.setFillColor(sf::Color(50, 255, 50, 50));
    detectionArea.setOutlineColor(sf::Color::Green);
    detectionArea.setOutlineThickness(2);
    detectionArea.setOrigin(radius, radius);
    detectionArea.setPosition(position);

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
    if (scanAngle >= 360.0f) scanAngle -= 360.0f;
    radarLine.setRotation(scanAngle);
    detectionGrid.update(deltaTime);

    for (auto it = detectionCooldowns.begin(); it != detectionCooldowns.end();) {
        it->second -= deltaTime;
        if (it->second <= 0.0f) it = detectionCooldowns.erase(it);
        else ++it;
    }

    if (isDetecting) {
        blinkTimer -= deltaTime;
        float alpha = 50 + 205 * (0.5f + 0.5f * std::sin(blinkTimer * 20.0f));
        detectionArea.setFillColor(sf::Color(50, 255, 50, static_cast<sf::Uint8>(alpha)));
        if (blinkTimer <= 0.0f) {
            isDetecting = false;
            detectionArea.setFillColor(sf::Color(50, 255, 50, 50));
        }
    }
}

void Radar::draw(sf::RenderWindow& window) {
    window.draw(detectionArea);
    window.draw(radarPoint);
    window.draw(radarLine);
}

void Radar::scan(const std::vector<Object>& objects) {
    bool detected = false;
    std::unordered_map<std::string, sf::Vector2f> currentDetections;
    const float LINE_WIDTH = 2.0f;

    for (const auto& obj : objects) {
        const std::string objName = obj.getName();
        sf::Vector2f objPosition = obj.getPosition();
        float dx = objPosition.x - position.x;
        float dy = objPosition.y - position.y;
        float distance = std::sqrt(dx * dx + dy * dy);

        if (distance <= radius && detectionCooldowns.find(objName) == detectionCooldowns.end()) {
            bool validDetection = false;
            float angularThreshold = std::atan2(LINE_WIDTH, distance) * (1.0f + (distance/radius));

            if (distance < 1e-3) {
                validDetection = true;
            } else {
                float rayAngle = scanAngle * M_PI / 180.0f;
                float angleToObj = std::atan2(dy, dx);
                float angleDifference = angleToObj - rayAngle;

                angleDifference = std::fmod(angleDifference, 2 * M_PI);
                if (angleDifference > M_PI) angleDifference -= 2 * M_PI;
                else if (angleDifference < -M_PI) angleDifference += 2 * M_PI;

                if (std::abs(angleDifference) < angularThreshold) validDetection = true;
            }

            if (validDetection) {
                detectionGrid.addDetection(objPosition - position, 1.0f);
                detected = true;
                currentDetections[objName] = objPosition;
            }
        }
    }

    for (const auto& detection : currentDetections) {
        detectionCooldowns[detection.first] = 1.0f;
    }

    if (detected) {
        isDetecting = true;
        blinkTimer = 1.0f;
    }
}

void Radar::drawDetectionGrid(sf::RenderWindow& window) {
    detectionGrid.draw(window);
}
