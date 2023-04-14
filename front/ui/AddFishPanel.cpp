#include "../include/AddFishPanel.hpp"
#include "../include/TextureData.hpp"

#include <iostream>

AddFishPanel::AddFishPanel()
        : mAddFishButton {100, 100, SpriteProperties[SPROP::BUTTON]}
{
    std::cout << "AddFishPanel constructor" << std::endl;
}

AddFishPanel::~AddFishPanel()
{
    std::cout << "AddFishPanel destructor" << std::endl;
}


