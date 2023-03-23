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


#include "GraphNode.hpp"
#include <functional>
#include <string>

class UIElement : public GraphNode
{
public:
    using Ptr = std::unique_ptr<UIElement>;

    UIElement();
    UIElement(int,int);

    virtual ~UIElement();

    void         toggle(std::string arg ="");
    virtual void action() = 0;

    void    setCallback(std::function<std::string(std::string)>);

    void    attachSubElement(Ptr);
    Ptr     detachSubElement(Ptr);

private:
    std::function<std::string(std::string)> mCallback;
    std::vector<Ptr>                        mSubElements;
    UIElement *                             mParentElement;
};