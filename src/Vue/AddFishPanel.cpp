#include "include/AddFishPanel.hpp"
#include "include/TextureData.hpp"

#include <iostream>


AddFishPanel::AddFishPanel() : mAddFishButton {1600, 100,"", SpriteNode::Properties
        {
                .pathToTexture  = "../assets/addfishicon.png",
                .animated       = false,
                . textureSize   = { 0, 0, 800, 800 },
                .frameAmount    = {1}
        }
}
{
    mAddFishButton.setSize(100,100);
    std::cout << "AddFishPanel constructor" << std::endl;
}

AddFishPanel::~AddFishPanel()
{
    std::cout << "AddFishPanel destructor" << std::endl;
}

void AddFishPanel::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform*=getTransform();
    target.draw(mAddFishButton);
}

