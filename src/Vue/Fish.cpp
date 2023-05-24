#include "include/Fish.hpp"

Fish::Fish(FISH_TYPE FishType) 
: SpriteNode {FishSpriteProperties[(int)FishType]}
, mTrajectory{ TrajectoryFactory::staticTrajectory(0,0)}
, mElapsedTime{sf::Time::Zero}
, mTargetTime {sf::seconds(0.f)}
, mDirection { -1, 0 }
{

}

Fish::Fish(float posx, float posy, float targetx, float targety,float timeToTarget, FISH_TYPE FishType, FISH_BEHAVIOR FishBehavior)
: SpriteNode {FishSpriteProperties[(int)FishType]}
, mTrajectory { TrajectoryFactory::makeTrajectory(posx, posy, targetx, targety, timeToTarget, FishBehavior) }
, mElapsedTime{sf::Time::Zero}
, mTargetTime { sf::seconds(timeToTarget) }
, mDirection { -1, 0 }
{
    setPosition(posx, posy);
    setOrigin(FishSpriteProperties[(int)FishType].textureSize.width/2, FishSpriteProperties[(int)FishType].textureSize.height/2);
}

void Fish::updateCurrent(sf::Time dt)
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

void Fish::renewTarget(float targetx, float targety, float time, FISH_BEHAVIOR FishBehavior)
{
    mTargetTime = sf::seconds(time);
    mElapsedTime = sf::Time::Zero;
    sf::Vector2f pos = getPosition();
    mTrajectory = TrajectoryFactory::makeTrajectory(pos.x, pos.y, targetx, targety, time, FishBehavior);
}

void Fish::updateDirection(const sf::Vector2f& targetPosition)
{
    auto previousDirection = mDirection;
    mDirection = normalize(targetPosition - getPosition());

    // if(norm(mDirection) > 0.1)
    // {
    //     float angle = toDegrees(vectorsAngle(previousDirection, mDirection));
    //     rotate(angle);
    // }
}