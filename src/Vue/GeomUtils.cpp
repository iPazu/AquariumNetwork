#include "include/GeomUtils.hpp"
#include <cmath>

float distance(float x1, float y1, float x2, float y2)
{
    return std::sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

float distance(const sf::Vector2f& v1, const sf::Vector2f& v2)
{
    return distance(v1.x, v1.y, v2.x, v2.y);
}


float norm(const sf::Vector2f& v)
{
    return distance(sf::Vector2f(0,0), v);
}

float dotProduct(const sf::Vector2f& v1, const sf::Vector2f& v2)
{
    return  v1.x*v2.x + v1.y*v2.y;
}

float vectorAngle(const sf::Vector2f& v)
{
    sf::Vector2f flat {1,0};
    return std::acos(dotProduct(v, flat) / norm(v));
}

sf::Vector2f normalize(const sf::Vector2f& v)
{
    auto n = norm(v);
    return v/n;
}