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

UIElement::UIElement()
: mCallback {}
, mSubElements {}
{

}

UIElement::UIElement(int posx, int posy)
: mCallback {}
, mSubElements {}
{
    setPosition(posx, posy);
}

void UIElement::toggle(std::string arg)
{
    action();
    mCallback(arg);
}

void UIElement::setCallback(std::function<std::string(std::string)> callback)
{
    mCallback = callback;
}

void UIElement::attachSubElement(UIElement::Ptr element)
{
    element->mParentElement = this;
    mSubElements.push_back(std::move(element));
}

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
