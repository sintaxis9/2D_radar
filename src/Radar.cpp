#include "Radar.h"
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
                std::cout << "colision detectada" << std::endl;
                std::cout << "distancia: " << distance << " unidades" << std::endl;
                float clockPosition = (angleToObj * 180.0f / M_PI);
                clockPosition = std::fmod(clockPosition + 360.0f, 360.0f);
                int hourMark = static_cast<int>((clockPosition / 30.0f));
                std::string timeStr;

                switch (hourMark) {
                    case 0: timeStr = "3 en punto"; break;
                    case 1: timeStr = "4 en punto"; break;
                    case 2: timeStr = "5 en punto"; break;
                    case 3: timeStr = "6 en punto"; break;
                    case 4: timeStr = "7 en punto"; break;
                    case 5: timeStr = "8 en punto"; break;
                    case 6: timeStr = "9 en punto"; break;
                    case 7: timeStr = "10 en punto"; break;
                    case 8: timeStr = "11 en punto"; break;
                    case 9: timeStr = "12 en punto"; break;
                    case 10: timeStr = "1 en punto"; break;
                    case 11: timeStr = "2 en punto"; break;
                    default: timeStr = "direccion desconocida"; break;
                }
                std::cout << "direccion: " << timeStr << std::endl;
                std::cout << "--------------------------" << std::endl;
            }
        }
    }
}
