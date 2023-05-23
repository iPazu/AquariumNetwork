#include "include/Console.hpp"
#include "include/ClientController.hpp"
#include <algorithm>
#include <iostream>
#include "include/CommandParser.hpp"


void Console::initializeCommands() {
    mCommandParser->addCommand("hello", [this](const std::vector<std::string>& args) {
        // Implementation of hello command
        mClientController->addCommand("hello",args);
    });
    mCommandParser->addCommand("ping", [this](const std::vector<std::string>& args) {
        // Implementation of hello command
        mClientController->addCommand("ping",args);
    });
    mCommandParser->addCommand("addFish", [this](const std::vector<std::string>& args) {
        if (args.empty()) {
            println("Error: addFish command needs at least one argument");
            return;
        }
        mClientController->addCommand("addFish", args);
    });
    mCommandParser->addCommand("status", [this](const std::vector<std::string>& args) {
        // Implementation of hello command
        mClientController->addCommand("status",args);
    });
    mCommandParser->addCommand("getFishes", [this](const std::vector<std::string>& args) {
        // Implementation of hello command
        mClientController->addCommand("getFishes");
    });
    mCommandParser->addCommand("ls", [this](const std::vector<std::string>& args) {
        // Implementation of hello command
        mClientController->addCommand("ls");
    });


}

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
    mCommandParser = new CommandParser(*this);
    initializeCommands();


    loadFont();
}



Console::Console(float x, float y, float width, float height, ClientController &controller, unsigned int charSize)
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
, mClientController {&controller}
{
    //Initialize the command parser
    mCommandParser = new CommandParser(*this);
    initializeCommands();
    loadFont();
    mRect.setFillColor(sf::Color(0,0,0,150));
    mRect.setOutlineThickness(2.f);
    mRect.setOutlineColor(mNoFocusColor);
    setPosition(x,y);
}

Console::~Console() {
    delete mCommandParser;
}



const std::string Console::getLastCommand() const
{
    std::function<bool(const ConsoText&)> cond = [=](const ConsoText& t)
    {
        return t.second == TextType::Command;
    };

    auto lastCommand = std::find_if(mLog.rbegin(), mLog.rend(), cond);

    if(lastCommand != mLog.rend())
    {
        return lastCommand->first.getString().toAnsiString();
    }
    return "";
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
            mCommandParser->parse(getLastCommand());
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

        while(futureBottom + 2* mCharSize > mRect.getLocalBounds().height)
        {
            for(int i = mLog.size()-1; i > 0; --i)
            {
                auto placement = mLog[i-1].first.getPosition();
                mLog[i].first.setPosition(placement);
            }
            mLog.erase(mLog.begin());
            lastText = mLog[mLog.size()-1].first;
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
    
    mCurrentCommand.erase(std::remove(mCurrentCommand.begin(), mCurrentCommand.end(), '\n'), mCurrentCommand.cend());
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


