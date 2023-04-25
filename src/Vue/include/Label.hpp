/**
 * @file Label.hpp
 * @author grybouilli (grybouilli@outlook.fr)
 * @brief 
 * @version 0.1
 * @date 2023-04-01
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once

#include "GraphNode.hpp"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <string>

class Label : public GraphNode
{
public:
    Label();
    Label(std::string, std::string , unsigned int = 30);

    void setText(std::string);
    void setFillColor(sf::Color);
    void setOutlineColor(sf::Color);
    void setFontSize(unsigned int);

    bool loadFontFrom(std::string);

private:
    virtual void    drawCurrent(sf::RenderTarget&, sf::RenderStates) const;

    sf::Font    mFont;
    sf::Text    mText;
};