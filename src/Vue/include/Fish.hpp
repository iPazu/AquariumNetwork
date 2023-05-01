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

    explicit Fish(FISH_TYPE FishType) 
    : SpriteNode {FishSpriteProperties[(int)FishType]}
    , mTrajectory{ TrajectoryFactory::staticTrajectory(0,0)}
    , mElapsedTime{sf::Time::Zero}
    , mTargetTime {sf::seconds(0.f)}
    , mDirection { -1, 0 }
    {

    }

    Fish(float posx, float posy, float targetx, float targety,float timeToTarget, FISH_TYPE FishType, FISH_BEHAVIOR FishBehavior)
    : SpriteNode {FishSpriteProperties[(int)FishType]}
    , mTrajectory { TrajectoryFactory::makeTrajectory(posx, posy, targetx, targety, timeToTarget, FishBehavior) }
    , mElapsedTime{sf::Time::Zero}
    , mTargetTime { sf::seconds(timeToTarget) }
    , mDirection { -1, 0 }
    {
        setPosition(posx, posy);
    }

    virtual void updateCurrent(sf::Time dt) 
    {
        mElapsedTime += dt;
        if(mElapsedTime < mTargetTime)
        {
            auto targetPosition = mTrajectory(mElapsedTime);
            updateDirection(targetPosition);
            setPosition(targetPosition);
        }
        animate(dt);

    }

    void renewTarget(float targetx, float targety, float time, FISH_BEHAVIOR FishBehavior = FISH_BEHAVIOR::LINEAR)
    {
        mTargetTime = sf::seconds(time);
        mElapsedTime = sf::Time::Zero;
        sf::Vector2f pos = getPosition();
        mTrajectory = TrajectoryFactory::makeTrajectory(pos.x, pos.y, targetx, targety, time, FishBehavior);
    }

private:
    void updateDirection(const sf::Vector2f& targetPosition)
    {
        auto previousDirection = mDirection;
        mDirection = normalize(targetPosition - getPosition());
        float angle = toDegrees(vectorsAngle(previousDirection, mDirection));
        rotate(angle);

        if(mDirection.x > 0 && getScale().y > 0)
        {

            setScale(getScale().x,-getScale().y);
        } else if (mDirection.x <= 0 && getScale().y < 0)
        {
            setScale(-getScale().x,getScale().y);
        }
    }
private:
    Trajectory    mTrajectory;
    sf::Time      mElapsedTime;
    sf::Time      mTargetTime;
    sf::Vector2f  mDirection;
};
