#pragma once

#include "SpriteNode.hpp"
#include <vector>

static const std::vector<SpriteNode::Properties> SpriteProperties =
{
    SpriteNode::Properties
    {
        .pathToTexture  = "../assets/angry.png",
        .animated       = false,
        . textureSize   = { 0, 0, 640, 624 },
        .frameAmount    = {1},
        .animationTime  = {sf::Time::Zero}
    },
    SpriteNode::Properties 
    {
        .pathToTexture  = "../assets/button.png",
        .animated       = true,
        .textureSize    = { 0, 0, 512, 256 },
        .frameAmount    = {2},
        .animationTime  = {sf::Time::Zero}
    }
};

enum SPROP 
{
    ANGRY,
    BUTTON,
    TOTAL
};