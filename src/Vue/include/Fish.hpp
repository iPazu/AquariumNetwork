/**
 * @file Fish.hpp
 * @author grybouilli (grybouilli@outlook.fr)
 * @brief 
 * @version 0.1
 * @date 2023-04-02
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once

#include "FishTypes.hpp"
#include "FishBehavior.hpp"
#include "SpriteNode.hpp"
#include "IOUtils.hpp"
#include "GeomUtils.hpp"
#include <iostream>

class Fish : public SpriteNode
{
public:

    explicit Fish(FISH_TYPE FishType);

    Fish(float posx, float posy, float targetx, float targety,float timeToTarget, FISH_TYPE FishType, FISH_BEHAVIOR FishBehavior);

    virtual void updateCurrent(sf::Time dt);

    void renewTarget(float targetx, float targety, float time, FISH_BEHAVIOR FishBehavior = FISH_BEHAVIOR::LINEAR);

private:
    void updateDirection(const sf::Vector2f& targetPosition);
private:
    Trajectory    mTrajectory;
    sf::Time      mElapsedTime;
    sf::Time      mTargetTime;
    sf::Vector2f  mDirection;
    bool          mStarted;
};
