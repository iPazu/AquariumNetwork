/**
 * @file SpriteNode.cpp
 * @author grybouilli (grybouilli@outlook.fr)
 * @brief 
 * @version 0.1
 * @date 2023-03-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <stdexcept>
#include "include/SpriteNode.hpp"

SpriteNode::SpriteNode()
: mProperties {}
, mTexture {}
, mSprite {}
, mCurrentSprite{0,0}
, mElapsedTime { sf::Time::Zero }
{

}

SpriteNode::SpriteNode(const Properties& p)
: mProperties { std::move(p) }
, mTexture { }
, mSprite { }
, mCurrentSprite{0,0}
, mElapsedTime { sf::Time::Zero }
{
    loadTexture();
}

/**
 * @brief Set new properties for the SpriteNode object.
 * 
 * @param p The new Properties struct.
 */
void SpriteNode::setup(const Properties& p)
{
    mProperties = std::move(p);
    loadTexture();
}

sf::FloatRect SpriteNode::getBoundRect() const
{
    return mSprite.getGlobalBounds();
}

void SpriteNode::setSize(int width, int height)
{
    sf::Vector2f scale { (float)(width) / mProperties.textureSize.width, (float)(height) / mProperties.textureSize.height };
    setScale(scale);
}

void SpriteNode::setSize(sf::Vector2i size)
{
    setSize(size.x, size.y);
}

sf::Vector2f SpriteNode::getSize() const
{
    auto scale = getScale();
    auto textureRect = mSprite.getTextureRect();
    return sf::Vector2f(scale.x * textureRect.width, scale.y*textureRect.height);
}


void SpriteNode::goToNextAnimationFrame()
{
    sf::Vector2u textSize       = mTexture.getSize();
    sf::IntRect currentTextRect = mSprite.getTextureRect();

    mCurrentSprite.second++;
    mCurrentSprite.second %= mProperties.frameAmount[mCurrentSprite.first];
    sf::IntRect newTextRect { 
        mCurrentSprite.second * currentTextRect.width, 
        currentTextRect.top + mCurrentSprite.first * mProperties.textureSize.height, 
        currentTextRect.width, 
        currentTextRect.height };

    mSprite.setTextureRect(newTextRect);
}
/**
 * @brief Texture loading function.
 * 
 * Ensure that the texture exists and that the properties set in the SpriteNode are adapted to the loaded texture. Two errors can be thrown:
 *  - Texture not found;
 *  - Invalid texture properties (for example, the texture rectangle is too wide for the texture).
 * 
 */
void SpriteNode::loadTexture()
{
    if (!mTexture.loadFromFile(mProperties.pathToTexture)) {
        throw std::runtime_error("ERROR: could not find texture : " + mProperties.pathToTexture);
    }

    auto textureSize = mTexture.getSize();
    if(textureSize.x < mProperties.frameAmount[mCurrentSprite.first] * mProperties.textureSize.width || textureSize.y < mProperties.textureSize.height)
    {
        throw std::logic_error("ERROR: invalid texture properties; out of bound frameAmount or invalid textureSize for texture : " + mProperties.pathToTexture );
    }

    mSprite.setTexture(mTexture);
    mSprite.setTextureRect(mProperties.textureSize);
}

/**
 * @brief Move to next animation frame.
 * 
 * Move the texture rectangle of the sprite to the next animation frame according to settings stored in the properties of the SpriteNode. The frame should be stored in line on the frames file.
 * 
 */
void SpriteNode::animate(sf::Time dt)
{
    if(mProperties.animated)
    {
        mElapsedTime += dt;
        if(mElapsedTime >= mProperties.animationTime[mCurrentSprite.first])
        {
            goToNextAnimationFrame();
            mElapsedTime = sf::Time::Zero;
        }
    }
       
}

void SpriteNode::setToAnimation(int animNumber)
{
    if(animNumber >= mProperties.frameAmount.size())
    {
        throw std::runtime_error("SpriteNode: animNumber requested is too high (" + std::to_string(animNumber) + "); the maximum was " + std::to_string(mProperties.frameAmount.size()-1) );
    }
    mCurrentSprite.first = animNumber;

    sf::IntRect currentTextRect = mSprite.getTextureRect();
    sf::IntRect newTextRect { 
        0, 
        mCurrentSprite.first * mProperties.textureSize.height, 
        currentTextRect.width, 
        currentTextRect.height };

    mSprite.setTextureRect(newTextRect);
}

int SpriteNode::getCurrentAnimationNumber() const
{
    return mCurrentSprite.first;
}

void SpriteNode::setTextureTo(int x, int y, int width, int height)
{
    sf::IntRect newRec {x, y, width, height};
    mSprite.setTextureRect(newRec);
}


/**
 * @brief Update current sprite object.
 * 
 * If the sprite is animated, will move to the next frame of animation.
 * 
 * @param dt Elapsed time since last call to update.
 */
void SpriteNode::updateCurrent(sf::Time dt)
{
    if(mProperties.animated)
        animate(dt);   
}

/**
 * @brief Draw SpriteNode object to target with states.
 * 
 * @param target The target to draw on.
 * @param states The states to apply when drawind the sprite.
 */
void SpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}