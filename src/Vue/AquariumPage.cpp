#include "include/AquariumPage.hpp"


AquariumPage::AquariumPage(const SpriteNode::Properties& aProp, int ax, int ay, int w, int h)
: mAquarium {ax, ay, w, h, aProp }
{

}

void AquariumPage::handleEvents(const sf::Event& event, sf::Vector2i mouse)
{
}

Page::Type AquariumPage::getPageType() const
{
    return Page::Type::Aquarium;
}

Aquarium * AquariumPage::getAquarium()
{
    return &mAquarium;
}