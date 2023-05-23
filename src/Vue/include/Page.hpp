#pragma once


#include "GraphNode.hpp"
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

class Page : public GraphNode
{
public:
    virtual ~Page(){}

    enum class Type
    {
        Welcome,
        VueSelection,
        Aquarium,
        TOTAL
    };

    virtual void handleEvents(const sf::Event&, sf::Vector2i) = 0;

    virtual Type getPageType() const = 0;

};