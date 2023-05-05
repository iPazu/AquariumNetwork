#include "include/Console.hpp"
#include <algorithm>
#include <iostream>

Console::Console()
: mFont {}
, mLog {}
, mCurrentCommand {}
, mRect { sf::Vector2f(0.f,0.f)}
, mHasFocus { false }
, mFocusColor { sf::Color::Blue }
, mNoFocusColor { sf::Color(100, 100, 100)}
, mCommandColor {sf::Color::White}
, mMessageColor {sf::Color::Yellow}
, mOffsets {}
{
    loadFont();
}

Console::Console(float x, float y, float width, float height, unsigned int charSize)
: mFont {}
, mCurrentCommand {}
, mCharSize {charSize} 
, mLog {}
, mRect { sf::Vector2f(width, height)}
, mHasFocus { false }
, mFocusColor { sf::Color::Blue }
, mNoFocusColor { sf::Color(100, 100, 100)}
, mCommandColor {sf::Color::White}
, mMessageColor {sf::Color::Yellow}
, mOffsets {charSize/2.f, charSize/2.f}
{
    loadFont();
    mRect.setFillColor(sf::Color(0,0,0,150));
    mRect.setOutlineThickness(2.f);
    mRect.setOutlineColor(mNoFocusColor);
    setPosition(x,y);
}

const std::string Console::getLastCommand() const
{
    std::function<bool(const ConsoText&)> cond = [=](const ConsoText& t)
    {
        return t.second == TextType::Command;
    };

    return std::find_if(mLog.rbegin(), mLog.rend(), cond)->first.getString().toAnsiString();
}

void Console::println(std::string theMessage)
{
    std::string buffer = mCurrentCommand;
    mCurrentCommand = theMessage;
    addNewText(Message);
    mCurrentCommand = buffer;
}

bool Console::hasFocus() const
{
    return mHasFocus;
}

void Console::handleEvent(sf::Event event)
{
    if (!mHasFocus)
        return;

    if(event.type == sf::Event::TextEntered)
    {
        auto lastEndline = std::find(mCurrentCommand.rbegin(), mCurrentCommand.rend(), '\n');
        lastEndline = lastEndline == mCurrentCommand.rend()? mCurrentCommand.rend()-1 : lastEndline;

        if (event.text.unicode == 8){   // Delete key
            mCurrentCommand = mCurrentCommand.substr(0, mCurrentCommand.size() - 1);
        } else if(event.key.code != sf::Keyboard::Escape){
            if (std::distance(mCurrentCommand.rbegin(), lastEndline)*mCharSize < mRect.getLocalBounds().width){
                mCurrentCommand += event.text.unicode;
            } else
            {
                std::cout << "thing is too long" << std::endl;
                mCurrentCommand += '\n';
                mCurrentCommand += event.text.unicode;
            }
        }
    }

    if(event.type == sf::Event::KeyReleased )
    {
        switch (event.key.code)
        {
        case sf::Keyboard::Enter:
            addNewText(TextType::Command);   
            break;

        case sf::Keyboard::Escape:
            std::cout << "escaping" << std::endl;
            setFocus(false);
        
        default:
            break;
        }
    }

    // handle mouse pressed ?
}

bool Console::isPointIn(float x, float y) const
{
    return getTransform().transformRect(mRect.getLocalBounds()).contains(x,y);
}

unsigned int Console::flushFor(sf::Text newText)
{
    if(mLog.size() > 0)
    {
        auto lastText = mLog[mLog.size()-1].first;
        auto futureBottom = lastText.getLocalBounds().height  + lastText.getPosition().y+mOffsets.y;

        while(futureBottom + mCharSize > mRect.getLocalBounds().height)
        {
            auto occupation = mLog[0].first.getLocalBounds().height+mOffsets.y;
            mLog.erase(mLog.begin());
            lastText = mLog[mLog.size()-1].first;
            for(auto & texts: mLog)
            {
                texts.first.move(0, -occupation);
            }
            futureBottom = lastText.getLocalBounds().height + mOffsets.y + lastText.getPosition().y;
        }
        return futureBottom;
    }
    return mCharSize;
}


void Console::setFocus(bool focus)
{
    mHasFocus = focus;
    mRect.setOutlineColor(focus ? mFocusColor : mNoFocusColor);
}


void Console::addNewText(TextType textType)
{
    if(mCurrentCommand.size()==0)
        return;
    sf::Text newCommand {mCurrentCommand, mFont, mCharSize};
    
    newCommand.setPosition(mCharSize, flushFor(newCommand));

    newCommand.setFillColor(textType == TextType::Command? mCommandColor : mMessageColor);

    mLog.push_back(std::make_pair(newCommand, textType));
    mCurrentCommand = "";
}

void Console::action()
{
    setFocus(true);
}

void Console::loadFont()
{
    if(!mFont.loadFromFile("../assets/ConsoleFont.ttf"))
    {
        throw std::runtime_error("Label : Could not load ConsoleFont.ttf");
    }
}


void Console::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mRect, states);
    for(auto& text : mLog)
    {
        target.draw(text.first, states);
    }
    if(mHasFocus)
    {
        sf::Text current {mCurrentCommand, mFont, mCharSize};
        current.setPosition(mCharSize, mRect.getLocalBounds().height);
        current.setFillColor(mCommandColor);
        
        sf::RectangleShape prompt{ sf::Vector2f(mRect.getSize().x, current.getLocalBounds().height+mCharSize) };
        prompt.setFillColor(sf::Color(0,0,0,150));
        prompt.setOutlineThickness(2.f);
        prompt.setOutlineColor(mFocusColor);
        prompt.setPosition(0, mRect.getLocalBounds().height);
        target.draw(prompt, states);
        target.draw (current, states);
    }
}