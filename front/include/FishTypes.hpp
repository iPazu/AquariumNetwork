#pragma once

#include "SpriteNode.hpp"
#include <vector>

enum class FISH_TYPE
{
    CLOWN,
    GOLDEN,
    TOTAL
};

static const std::vector<SpriteNode::Properties> FishSpriteProperties =
{
    SpriteNode::Properties
    {
        .pathToTexture  = "../assets/clown.png",
        .animated       = false,
        . textureSize   = { 0, 0, 600, 600 },
        .frameAmount    = {1}
    },
    
    SpriteNode::Properties
    {
        .pathToTexture  = "../assets/angry.png",
        .animated       = false,
        . textureSize   = { 0, 0, 640, 624 },
        .frameAmount    = {1}
    }
};