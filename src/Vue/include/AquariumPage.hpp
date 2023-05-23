#pragma once

#include "Page.hpp"
#include "Aquarium.hpp"

class AquariumPage : public Page
{
public:
    explicit AquariumPage(const SpriteNode::Properties&, int, int, int, int);

    virtual void handleEvents(const sf::Event&, sf::Vector2i);

    virtual Type getPageType() const;

    Aquarium * getAquarium();

private:
    Aquarium    mAquarium;

};