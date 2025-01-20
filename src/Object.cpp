#include "../include/Object.h"

Object::Object(std::string name, sf::Vector2f position, float radius)
    : name(name), position(position), radius(radius) {}
std::string Object::getName() const {
    return name;
}
sf::Vector2f Object::getPosition() const {
    return position;
}
float Object::getRadius() const {
    return radius;
}
