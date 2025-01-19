#ifndef OBJECT_H
#define OBJECT_H

#include <SFML/Graphics.hpp>
#include <string>

class Object {
public:
    Object(std::string name, sf::Vector2f position, float radius);

    std::string getName() const;
    sf::Vector2f getPosition() const;
    float getRadius() const;

private:
    std::string name;
    sf::Vector2f position;
    float radius;
};

#endif
