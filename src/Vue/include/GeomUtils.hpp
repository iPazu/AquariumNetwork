#pragma once

#include <SFML/System/Vector2.hpp>

float distance(float, float, float, float);
float distance(const sf::Vector2f&, const sf::Vector2f&);

float norm(const sf::Vector2f&);
float dotProduct(const sf::Vector2f&, const sf::Vector2f&);
float vectorAngle(const sf::Vector2f&);

sf::Vector2f normalize(const sf::Vector2f&);