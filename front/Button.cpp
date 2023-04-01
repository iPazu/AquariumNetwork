/**
 * @file Button.cpp
 * @author grybouilli (grybouilli@outlook.fr)
 * @brief 
 * @version 0.1
 * @date 2023-03-31
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "include/Button.hpp"

Button::Button(const SpriteNode::Properties& prop)
: SpriteNode(prop)
, mIsToggled { false }
, mLabel {"Button", "../assets/Fishermills.ttf"}
{
    mLabel.setFillColor(sf::Color::Black);
    Label::Ptr ptr { &mLabel }; 
    attachChild(std::move(ptr));
}

Button::Button(int x, int y, const SpriteNode::Properties& prop)
: UIElement()
, SpriteNode(prop)
, mIsToggled { false }
, mLabel {"Button", "../assets/Fishermills.ttf"}
{
    setPosition(x,y);
    mLabel.setFillColor(sf::Color::Black);
    mLabel.setPosition(prop.textureSize.width/2, prop.textureSize.height/2);
    Label::Ptr ptr { &mLabel }; 
    attachChild(std::move(ptr));
}

void Button::select(std::string arg)
{
    toggle(arg);
}

void Button::deselect()
{
    action();
}

void Button::setLabel(std::string label)
{
    mLabel.setText(label);
}

bool Button::isToggled() const
{
    return mIsToggled;
}

bool Button::isOnButton(int x, int y) const
{
    return getTransform().transformRect(getBoundRect()).contains(x,y);
}

void Button::action()
{
    animate();
    mIsToggled = !mIsToggled;
}