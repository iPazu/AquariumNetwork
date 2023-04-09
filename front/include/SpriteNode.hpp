/**
 * @file SpriteNode.hpp
 * @author grybouilli (grybouilli@outlook.fr)
 * @brief 
 * @version 0.1
 * @date 2023-03-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once

#include "GraphNode.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <string>
#include <vector>
/**
 * @brief Base class for sprite element.
 * 
 * The sprite can be animated or not. It needs to be supplied a Sprite::Properties to be displayed. Sprite::Properties contains information about the path to the Sprite texture, it's size and whether it's animated or not.
 * 
 */
class SpriteNode : public GraphNode
{
public:
    /**
     * @brief Properties for SpriteNode object. 
     */
    struct Properties
    {
        std::string         pathToTexture;  ///< The path to the sprite texture.
        bool                animated;       ///< True if the sprite is animated.
        sf::IntRect         textureSize;    ///< The texture rectangle (size of frame)
        std::vector<int>    frameAmount;    ///< The amount of frame (1 if animated = false)
        
    };

    SpriteNode();
    SpriteNode(const Properties&);

    void setup(const Properties&);

    sf::FloatRect   getBoundRect() const;

    void            setSize(int,int);
    void            setSize(sf::Vector2i);

    sf::Vector2f    getSize() const;

protected:
    void            animate();
    void            setToAnimation(int);

private:
    void            loadTexture();

    virtual void    updateCurrent(sf::Time);
    virtual void    drawCurrent(sf::RenderTarget&, sf::RenderStates) const;

    Properties      mProperties;
    sf::Texture     mTexture;
    sf::Sprite      mSprite;
    int             mCurrentSprite;
};