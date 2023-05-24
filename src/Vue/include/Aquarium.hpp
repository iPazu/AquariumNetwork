#pragma once

#include "FishTypes.hpp"
#include "SpriteNode.hpp"
#include "Fish.hpp"
#include <string>
#include <map>

class Aquarium : public SpriteNode
{
public: 
    Aquarium();
    Aquarium(const SpriteNode::Properties&);
    Aquarium(int, int, int, int, const SpriteNode::Properties&);

    virtual ~Aquarium();

    using FishID = std::string;

    bool            addFish(const FishID& fishID, FISH_TYPE fishType, int posx = 0, int posy = 0, int sizex = 1, int sizey = 1, int targetx = 0 , int targety = 0,float timeToTarget = 0.f,  FISH_BEHAVIOR FishBehavior = FISH_BEHAVIOR::LINEAR);
    bool            removeFish(const FishID& fishID);

    void            setFishTarget(const FishID& fishID, int targetx, int targety, float timeToTarget);

    bool            isFishInAquarium(FishID) const;

    void            setAquariumAt(int, int);
    
private:

    sf::Vector2f    toAquariumScaling(int percentageX, int percentageY);
    virtual void    drawCurrent(sf::RenderTarget&, sf::RenderStates) const;
    virtual void    updateCurrent(sf::Time);

private:
    std::map<FishID, Fish *> mFishes;

    sf::Vector2i            mSize;

};