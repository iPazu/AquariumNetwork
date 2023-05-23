#pragma once

#include "Page.hpp"
#include "SpriteNode.hpp"

class WelcomePage : public Page
{
public:
    WelcomePage();
    WelcomePage(const SpriteNode::Properties&, int width, int height);

    virtual ~WelcomePage();

    virtual void handleEvents(const sf::Event&, sf::Vector2i);

    virtual Type getPageType() const;

private:
    virtual void updateCurrent(sf::Time) ;

    // virtual void drawCurrent(sf::RenderTarget&, sf::RenderStates) const;

    SpriteNode      mBackground;
};