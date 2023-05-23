#pragma once

#include "Button.hpp"

class VueButton : public Button
{
public:
    explicit VueButton(const SpriteNode::Properties&);
    VueButton(int,int,const char * label,const SpriteNode::Properties&);

    void    hover();
    void    unhover();

    bool    isHovered() const;
    
private:
    virtual void drawCurrent(sf::RenderTarget&, sf::RenderStates) const;

    bool    mIsHovered;


};