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

/*!
 * @brief Button constructor.
 * 
 * Construct a button from a set of SpriteNode properties.
 * 
 * @param prop The properties set of the button to create.
 */

Button::Button(const SpriteNode::Properties& prop)
: SpriteNode(prop)
, mIsToggled { false }
, mLabel {"Button", "../assets/Fishermills.ttf"}
{
    mLabel.setFillColor(sf::Color::Black);
    Label::Ptr ptr { &mLabel }; 
    attachChild(std::move(ptr));
}

/*!
 * @brief Button constructor.
 * 
 * Construct a button from a set of SpriteNode properties and position it at coordinates (x,y).
 *
 * @param x 
 * @param y 
 * @param prop 
 */
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

Button::~Button()
{
    auto labelPtr = std::move(detachChild(mLabel));
    labelPtr.release();
}
/*!
 * @brief Select button.
 *
 * @param arg Argument passed on to the callback.
 */
void Button::select(std::string arg)
{
    toggle(arg);
}

/*!
 * @brief Deselect button.
 */
void Button::deselect()
{
    action();
}

/*!
 * @brief Changes button label.
 * @param label The new text attached to the label.
 */
void Button::setLabel(std::string label)
{
    mLabel.setText(label);
}

/*!
 * @brief Is the button toggled?
 * @return True if the button is currently toggled.
 */
bool Button::isToggled() const
{
    return mIsToggled;
}

/*!
 * @brief Is position (x,y) in the button bounds?
 *
 * @param x X Coord of the position to evaluate.
 * @param y Y Coord of the position to evaluate.
 * @return True if position (x,y) is contained in the button region.
 */
bool Button::isOnButton(int x, int y) const
{
    return getTransform().transformRect(getBoundRect()).contains(x,y);
}

void Button::action()
{
    animate();
    mIsToggled = !mIsToggled;
}