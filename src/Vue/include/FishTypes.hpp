#pragma once

#include "SpriteNode.hpp"
#include <vector>
#include <SFML/System/Time.hpp>
#include <random>

enum class FISH_TYPE
{
    BLUE,
    SHARK,
    UGLY,
    TOTAL
};

FISH_TYPE getRandomFishType();

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
        .pathToTexture  = "../assets/shark.png",
        .animated       = true,
        . textureSize   = { 0, 0, 98, 44 },
        .frameAmount    = {3},
        .animationTime = {sf::seconds(.5f)}
    },

    SpriteNode::Properties
    {
        .pathToTexture  = "../assets/blob.png",
        .animated       = true,
        . textureSize   = { 0, 0, 56, 60 },
        .frameAmount    = {16},
        .animationTime = {sf::seconds(.05f)}
    }

};