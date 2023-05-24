#include "include/Aquarium.hpp"


Aquarium::Aquarium()
: SpriteNode {}
{

}

Aquarium::Aquarium(const SpriteNode::Properties& prop)
: SpriteNode { prop }
{

}

Aquarium::Aquarium(int x, int y, int width, int height, const SpriteNode::Properties& prop)
: SpriteNode { prop }
, mSize {width, height}
{
    setTextureTo(x, y, width, height);
}

Aquarium::~Aquarium()
{
    for (const auto& [fishId, fish] : mFishes)
    {
        delete fish;
    }
}

bool Aquarium::addFish(const FishID& fishID, FISH_TYPE fishType, int posx, int posy, int sizex, int sizey, int targetx, int targety, float timeToTarget,  FISH_BEHAVIOR FishBehavior)
{
    if(mFishes.contains(fishID))
    {
        return false;
    }

    sf::Vector2f fishPosition = toAquariumScaling(posx, posy);
    sf::Vector2f targetPosition = toAquariumScaling(targetx, targety);

    Fish * newFish = new Fish(
        fishPosition.x,
        fishPosition.y,
        targetPosition.x,
        targetPosition.y,
        timeToTarget,
        fishType,
        FishBehavior
    );
    sf::Vector2f fishSize = toAquariumScaling(sizex, sizey);
    newFish->setSize((int)fishSize.x, (int)fishSize.y);
    mFishes.emplace(fishID, newFish);
    return true;
}


bool Aquarium::removeFish(const FishID& fishID)
{
    if(!mFishes.contains(fishID))
    {
        return false;
    }

    mFishes.erase(fishID);

    return true;
}

void Aquarium::setFishTarget(const FishID& fishID, int targetx, int targety, float timeToTarget)
{
    std::cout << "Aquarium > current position : " << mFishes.find(fishID)->second->getPosition() << std::endl;
    sf::Vector2f targetPosition = toAquariumScaling(targetx, targety);
    mFishes.find(fishID)->second->renewTarget(targetPosition.x, targetPosition.y, timeToTarget);
}


bool Aquarium::isFishInAquarium(FishID fishID) const
{
    return mFishes.contains(fishID);
}

void Aquarium::setAquariumAt(int x, int y)
{
    setTextureTo(x, y, mSize.x, mSize.y);
}


sf::Vector2f Aquarium::toAquariumScaling(int percentageX, int percentageY)
{
    return sf::Vector2f(
        percentageX * getSize().x / 100.f, 
        percentageY * getSize().y / 100.f);
}


void Aquarium::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    SpriteNode::drawCurrent(target, states);
    for (const auto& [fishId, fish] : mFishes)
    {
        target.draw(*fish, states);
    }
}

void Aquarium::updateCurrent(sf::Time dt)
{
    for (const auto& [fishId, fish] : mFishes)
    {
        fish->update(dt);
    }
}

