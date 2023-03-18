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
{

}

SpriteNode::SpriteNode(const Properties& p)
: mProperties { std::move(p) }
, mTexture { }
, mSprite { }
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
    if(textureSize.x < mProperties.frameAmount * mProperties.textureSize.width || textureSize.y < mProperties.textureSize.height)
    {
        throw std::logic_error("ERROR: invalid texture properties; out of bound frameAmount or invalid textureSize for texture : " + mProperties.pathToTexture );
    }

    mSprite.setTexture(mTexture);
    mSprite.setTextureRect(mProperties.textureSize);
}

/**
 * @brief Move to next animation frame.
 * 
 * Move the texture rectangle of the sprite to the next animation frame according to settings stored in the properties of the SpriteNode.
 * 
 */
void SpriteNode::animate()
{
    sf::Vector2u textSize       = mTexture.getSize();
    sf::IntRect currentTextRect = mSprite.getTextureRect();

    sf::IntRect newTextRect { 
        (currentTextRect.left + mProperties.textureSize.width) % (mProperties.textureSize.width * mProperties.frameAmount), 
        currentTextRect.top, 
        currentTextRect.width, 
        currentTextRect.height };

    mSprite.setTextureRect(newTextRect);
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
        animate();
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