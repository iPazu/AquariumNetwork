#include "include/SelectionPage.hpp"
#include "include/VueButton.hpp"
#include "include/IOUtils.hpp"
#include <cmath>

SelectionPage::SelectionPage(const SpriteNode::Properties& propBackground, const SpriteNode::Properties& propButton, int width, int height, const std::vector<VueID_t>& vuePossibilities)
:  mBackground {propBackground}
{
    mBackground.setSize(width, height);

    const auto buttonSpace = width * (1 - buttonPad / 50);
    const auto buttonOccupation = width * (buttonWidth+buttonSpacing) / 100;

    const int colAmount = std::floor(buttonSpace/buttonOccupation);
    const int lineAmount = std::ceil(vuePossibilities.size()/colAmount);

    int line = 0;
    int column = 0;
    
    int buttonNb = 0;
    for(auto& vueID : vuePossibilities)
    {
        int butx = width * buttonPad / 100 + column * buttonOccupation;
        int buty = (height - lineAmount*(buttonSpacing+buttonHeight))/ 2 + line * height * (buttonSpacing+buttonHeight) / 100;

        std::string vueLabel = "Vue " + std::to_string(vueID);

        VueButton * newButton = new VueButton {propButton};
        newButton->setPosition(butx, buty);
        newButton->setLabel(vueLabel);
        newButton->setSize(buttonWidth*width/100, buttonHeight*height/100);
        mVueButtons.push_back(std::move(newButton));
        mVueIDs[buttonNb] = vueID;

        column++;
        column %= colAmount;
        if(column == 0)
            line++;   

        buttonNb++;
    }   
}

SelectionPage::~SelectionPage()
{
    for(auto& button: mVueButtons)
    {
        delete button;
    }    
}

void SelectionPage::handleEvents(const sf::Event& event, sf::Vector2i mouse)
{
    if(event.type == sf::Event::MouseButtonPressed)
    {
        std::cout << "mouse at : " << mouse << std::endl;
        for(auto& button: mVueButtons)
        {
            if(button->isOnButton(mouse.x, mouse.y))
            {
                std::cout << "button at : " << button->getPosition() << std::endl << std::endl;
                button->select();
                break;
            }
        }
    }

    if(event.type == sf::Event::MouseButtonReleased)
    {
        std::cout << "mouse at : " << mouse << std::endl;
        for(auto& button: mVueButtons)
        {
            if(button->isOnButton(mouse.x, mouse.y))
            {
                std::cout << "button at : " << button->getPosition() << std::endl << std::endl;
                button->deselect();
                break;
            }
        }
    }

    handleMouse(mouse);
}

Page::Type SelectionPage::getPageType() const
{
    return Page::Type::VueSelection;
}

bool SelectionPage::hasSelectedVue() const
{
    for(auto& button: mVueButtons)
    {
        if(button->isToggled())
        {
            return true;
        }
    }
    return false;
}

VueID_t SelectionPage::getSelectedVue() const
{
    for(int i = 0; i < mVueButtons.size(); ++i)
    {
        if(mVueButtons[i]->isToggled())
        {
            return mVueIDs.at(i);
        }
    }
    return NoneVue;
}

void SelectionPage::handleMouse(sf::Vector2i mouse)
{
    for(auto& button: mVueButtons)
    {
        if(button->isOnButton(mouse.x, mouse.y))
        {
            button->hover();
        } else if(button->isHovered())
        {
            button->unhover();
        }
    }
}


void SelectionPage::updateCurrent(sf::Time dt)
{
    for(auto& button: mVueButtons)
    {
        button->update(dt);
    }
}

void SelectionPage::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mBackground, states);
    for(const auto& button: mVueButtons)
    {
        target.draw(*button, states);
    }
}