#include "include/Label.hpp"

Label::Label()
: mFont {}
, mText {}
{

}

Label::Label(std::string text, std::string pathToFont, unsigned int fontSize)
: mFont {}
, mText {text, mFont, fontSize}
{
    loadFontFrom(pathToFont);
}

void Label::setText(std::string text)
{
    mText.setString(text);
}

void Label::setFillColor(sf::Color color)
{
    mText.setFillColor(color);
}

void Label::setOutlineColor(sf::Color color)
{
    mText.setOutlineColor(color);
}

void Label::setFontSize(unsigned int size)
{
    mText.setCharacterSize(size);
}

bool Label::loadFontFrom(std::string path)
{
    if(!mFont.loadFromFile(path))
    {
        throw std::runtime_error("Label : Could not load " + path);

        return false;
    }
    return true;
}

void Label::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mText, states);
}