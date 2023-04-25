/**
 * @file Button.hpp
 * @author grybouilli (grybouilli@outlook.fr)
 * @brief UI Button class file
 * @version 0.1
 * @date 2023-03-31
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once

#include "UIElement.hpp"
#include "SpriteNode.hpp"
#include "Label.hpp"
#include <string>

/**
 * @brief UI Button class
 * 
 * You can select, deselect and add a callback function to this button. It benefits from all the features of the classes UIElement and SpriteNode.
 */
class Button : public UIElement, public SpriteNode
{
public:
    explicit Button(const SpriteNode::Properties&);
    Button(int,int,const char * label,const SpriteNode::Properties&);

    virtual ~Button();

    void            select(std::string arg = "");
    void            deselect();

    void            setLabel(std::string);

    bool            isToggled() const;
    bool            isOnButton(int, int) const;

private:
    virtual void    action();
    bool            mIsToggled;
    Label           mLabel;
};