#include "include/FishTypes.hpp"

FISH_TYPE getRandomFishType()
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> randFishId((int)FISH_TYPE::BLUE, (int)FISH_TYPE::TOTAL - 1); 

    return (FISH_TYPE)randFishId(rng);
}