/**
 * @file UIElement.cpp
 * @author grybouilli (grybouilli@outlook.fr)
 * @brief 
 * @version 0.1
 * @date 2023-03-23
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "include/UIElement.hpp"
#include <stdexcept>

UIElement::UIElement()
: mCallback {[](std::string){ return "";}}
, mSubElements {}
{

}

UIElement::~UIElement()
{

}


/**
 * @brief toggle the element
 * 
 * Makes a call to action and to the callback function. 
 * @param arg Argument passed on to the callback.
 */
void UIElement::toggle(std::string arg)
{
    action();
    mCallback(arg);
}

/**
 * @brief Changes the callback of the element.
 * 
 * @param callback The new callback.
 */
void UIElement::setCallback(std::function<std::string(std::string)> callback)
{
    mCallback = callback;
}

/**
 * @brief Add element to sub-elements.
 * 
 * Attaches element to the tree of sub-elements of the current object. 
 *
 * @param element The element to attach to the tree.
 */
void UIElement::attachSubElement(UIElement::Ptr element)
{
    element->mParentElement = this;
    mSubElements.push_back(std::move(element));
}

/*!
 * @brief Detach sub-element from the current group.
 *
 * Detaches element from the tree of the current object's sub-elements and returns the pointer pointing to it.
 * 
 * @param element The element to detach.
 * @return The detached element.
 */
UIElement::Ptr UIElement::detachSubElement(UIElement::Ptr element)
{
    auto found = std::find_if(mSubElements.begin(), mSubElements.end(), [&] (Ptr& p) { return p.get() == element.get(); });
	
    if(found != mSubElements.end())
    {
        throw std::runtime_error("Detaching a child that isn't in this graph.");
    }

	Ptr result = std::move(*found);
	result->mParentElement = nullptr;

	mSubElements.erase(found);
	return result;
}
