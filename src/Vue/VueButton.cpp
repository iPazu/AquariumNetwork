#include "include/VueButton.hpp"
#include <SFML/Graphics/RectangleShape.hpp>

VueButton::VueButton(const SpriteNode::Properties& prop)
: Button(prop)
, mIsHovered { false }
{

}

VueButton::VueButton(int w, int h, const char * label, const SpriteNode::Properties& prop)
: Button(w,h,label, prop)
, mIsHovered { false }
{

}

void VueButton::hover()
{
    mIsHovered = true;
}

void VueButton::unhover()
{
    mIsHovered = false;
}

bool VueButton::isHovered() const
{
    return mIsHovered;
}

void VueButton::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    Button::drawCurrent(target, states);
    if(mIsHovered)
    {
        auto thisScale = getScale();
        sf::Vector2f theRectSize { getSize().x / thisScale.x, getSize().y / thisScale.y};
        sf::RectangleShape brighter { theRectSize };
        brighter.setFillColor(sf::Color(0,255,34,100));
        target.draw(brighter, states);
    }
}