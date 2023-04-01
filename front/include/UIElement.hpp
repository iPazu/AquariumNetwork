/**
 * @file UIElement.hpp
 * @author grybouilli (grybouilli@outlook.fr)
 * @brief 
 * @version 0.1
 * @date 2023-03-23
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once

#include <SFML/Graphics/Transformable.hpp>
#include <functional>
#include <string>
#include <memory>

class UIElement //: public sf::Transformable
{
public:
    using Ptr = std::unique_ptr<UIElement>;
    using Callback = std::function<std::string(std::string)>;
    UIElement();

    virtual ~UIElement();

    void    toggle(std::string arg ="");

    void    setCallback(std::function<std::string(std::string)>);

    void    attachSubElement(Ptr);
    Ptr     detachSubElement(Ptr);

private:
    virtual void        action() = 0;
    Callback            mCallback;
    std::vector<Ptr>    mSubElements;
    UIElement *         mParentElement;
};