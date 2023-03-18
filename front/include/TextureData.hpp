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
        .frameAmount    = 1
    }
};

enum SPROP 
{
    ANGRY,
    TOTAL
};