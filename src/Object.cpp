#include "Object.h"

Object::Object(std::string name, sf::Vector2f position, float radius)
    : name(name) {
    objectShape.setRadius(radius);
    objectShape.setFillColor(sf::Color::Red);
    objectShape.setPosition(position);
}

void Object::draw(sf::RenderWindow& window) {
    window.draw(objectShape);
}

sf::Vector2f Object::getPosition() const {
    return objectShape.getPosition();
}

std::string Object::getName() const {
    return name;
}
