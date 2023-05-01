#pragma once

#include "SpriteNode.hpp"
#include <vector>
#include <SFML/System/Time.hpp>

enum class FISH_TYPE
{
    BLUE,
    GOLDEN,
    TOTAL
};

static const std::vector<SpriteNode::Properties> FishSpriteProperties =
{
    SpriteNode::Properties
    {
        .pathToTexture  = "../assets/animatedFish.png",
        .animated       = true,
        . textureSize   = { 0, 0, 498, 316 },
        .frameAmount    = {6},
        .animationTime = {sf::seconds(.05f)}
    },
    
    SpriteNode::Properties
    {
        .pathToTexture  = "../assets/angry.png",
        .animated       = false,
        . textureSize   = { 0, 0, 640, 624 },
        .frameAmount    = {1},
        .animationTime = {sf::Time::Zero}
    }
};