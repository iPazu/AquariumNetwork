#pragma once 

#include "Page.hpp"
#include "VueButton.hpp"
#include "SpriteNode.hpp"
#include <vector>
#include <map>

#define buttonWidth 10
#define buttonHeight 5
#define buttonPad 20
#define buttonSpacing 5 

using VueID_t = int;

#define NoneVue -1

class SelectionPage : public Page
{
public:
    explicit SelectionPage(const SpriteNode::Properties&, const SpriteNode::Properties&, int, int, const std::vector<VueID_t>&);
    ~SelectionPage();

    virtual void handleEvents(const sf::Event&,sf::Vector2i);

    virtual Type getPageType() const;

    bool    hasSelectedVue() const;
    VueID_t getSelectedVue() const;

private:
    void    handleMouse(sf::Vector2i);

    void updateCurrent(sf::Time);
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

    std::vector<VueButton *>    mVueButtons;
    std::map<int, VueID_t>    mVueIDs;
    SpriteNode                mBackground;
    
};