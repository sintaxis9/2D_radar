#ifndef OBJECT_H
#define OBJECT_H

#include <SFML/Graphics.hpp>
#include <string>

class Object {
public:
    Object(std::string name, sf::Vector2f position, float radius);
    void draw(sf::RenderWindow& window);
    sf::Vector2f getPosition() const;
    std::string getName() const;

private:
    std::string name;
    sf::CircleShape objectShape;
};

#endif
