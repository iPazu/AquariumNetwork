/**
 * @file UIElement.hpp
 * @author grybouilli (grybouilli@outlook.fr)
 * @brief UIElement class file.
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
#include <vector>

/**
 * @brief UIElement class
 * 
 * Base class for UI elements; a UI element is toggable and can resort to a callback function when toggled. UI Elements can be grouped in trees of UI elements and sub elements. This base class manages the logic behind all that.
 * 
 */
class UIElement
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