#pragma once

#include <SFML/System/Vector2.hpp>
#include <iostream>

template<typename T>
std::ostream& operator<<(std::ostream& out, sf::Vector2<T> v)
{
    out << "(" << v.x << ", " << v.y << ")";
    return out;
}