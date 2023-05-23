#include "include/WelcomePage.hpp"

WelcomePage::WelcomePage()
: mBackground{}
{

}

WelcomePage::WelcomePage(const SpriteNode::Properties& prop, int width, int height)
: mBackground{ prop }
{
    mBackground.setSize(width, height);
    SpriteNode::Ptr ptr { &mBackground };
    attachChild(std::move(ptr));
}

WelcomePage::~WelcomePage()
{
    auto ptr = std::move(detachChild(mBackground));
    ptr.release();
}

void WelcomePage::handleEvents(const sf::Event& event, sf::Vector2i mosue)
{

}

Page::Type WelcomePage::getPageType() const
{
    return Page::Type::Welcome;
}

void WelcomePage::updateCurrent(sf::Time dt)
{
    mBackground.update(dt);
}

// void WelcomePage::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
// {
//     target.draw(mBackground, states);
// }