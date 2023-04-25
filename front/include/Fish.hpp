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
#include <iostream>

template<FISH_TYPE FishType>
class Fish : public SpriteNode
{
public:
    Fish() 
    : SpriteNode {FishSpriteProperties[(int)FishType]}
    , mTrajectory{ TrajectoryFactory::staticTrajectory(0,0)}
    , mElapsedTime{sf::Time::Zero}
    , mTargetTime {sf::seconds(0.f)}
    {}

    Fish(float posx, float posy, float targetx, float targety,float timeToTarget, FISH_BEHAVIOR FishBehavior)
    : SpriteNode {FishSpriteProperties[(int)FishType]}
    , mTrajectory { TrajectoryFactory::makeTrajectory(posx, posy, targetx, targety, timeToTarget, FishBehavior) }
    , mElapsedTime{sf::Time::Zero}
    , mTargetTime { sf::seconds(timeToTarget) }
    {
        setPosition(posx, posy);
    }

    void updateCurrent(sf::Time dt)
    {
        mElapsedTime += dt;
        if(mElapsedTime < mTargetTime)
        {
            setPosition(mTrajectory(mElapsedTime));
        } else
        {
        }
        animate(dt);
    }

    void renewTarget(float targetx, float targety, float time, FISH_BEHAVIOR FishBehavior)
    {
        mTargetTime = sf::seconds(time);
        mElapsedTime = sf::Time::Zero;
        sf::Vector2f pos = getPosition();
        mTrajectory = TrajectoryFactory::makeTrajectory(pos.x, pos.y, targetx, targety, time, FishBehavior);
    }
    
private:
    Trajectory    mTrajectory;
    sf::Time      mElapsedTime;
    sf::Time      mTargetTime;
};
