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
        .animated       = false,
        .textureSize    = { 0, 0, 512, 256 },
        .frameAmount    = {1,1},
        .animationTime  = {sf::Time::Zero}
    },
    SpriteNode::Properties
    {
        .pathToTexture  = "../assets/under_the_sea.png",
        .animated       = false,
        . textureSize   = { 0, 0, 5000, 4370 },
        .frameAmount    = {1},
        .animationTime  = {sf::Time::Zero}   
    },
    SpriteNode::Properties
    {
        .pathToTexture  = "../assets/welcome.png",
        .animated       = false,
        . textureSize   = { 0, 0, 590, 316 },
        .frameAmount    = {1},
        .animationTime  = {sf::Time::Zero}   
    },
    SpriteNode::Properties
    {
        .pathToTexture  = "../assets/under_the_sea.png",
        .animated       = false,
        . textureSize   = { 0, 0, 5000, 4370 },
        .frameAmount    = {1},
        .animationTime  = {sf::Time::Zero}   
    }
};

enum SPROP 
{
    ANGRY,
    BUTTON,
    AQUARIUM,
    WELCOMEPAGE,
    SELECTIONPAGE,
    TOTAL
};