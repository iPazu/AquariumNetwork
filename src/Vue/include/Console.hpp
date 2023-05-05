#pragma once

#include "UIElement.hpp"
#include "GraphNode.hpp"
#include "CommandParser.hpp"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Text.hpp>

class CommandParser;

class Console : public UIElement, public GraphNode
{
public:

    Console();
    Console(float,float,float,float, unsigned int = 24);
    ~Console();

    const std::string getLastCommand() const;

    void println(std::string);

    bool hasFocus() const;
    void handleEvent(sf::Event);
    void initializeCommands();


    bool isPointIn(float x, float y) const;
private:
    enum TextType
    {
        Command,
        Message
    };

    using ConsoText = std::pair<sf::Text, TextType>;

    void setFocus(bool focus);
    unsigned int flushFor(sf::Text);
    void addNewText(TextType);

    void action();

    void loadFont();

    virtual void    drawCurrent(sf::RenderTarget&, sf::RenderStates) const;

private:
    sf::Font            mFont;
    std::string         mCurrentCommand;
    CommandParser *mCommandParser;

    unsigned int        mCharSize;

    std::vector<ConsoText> mLog;

    sf::RectangleShape  mRect;
    
    bool                mHasFocus;

    sf::Color           mFocusColor;
    sf::Color           mNoFocusColor;

    sf::Color           mCommandColor;
    sf::Color           mMessageColor;

    sf::Vector2f        mOffsets;
};