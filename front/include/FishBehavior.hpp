#pragma once 


#include <functional>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Time.hpp>


enum class FISH_BEHAVIOR
{
    RANDOM,
    LINEAR,
    SINUSOIDAL,
    TOTAL
};

using Trajectory = std::function<sf::Vector2f(sf::Time)>;

class TrajectoryFactory
{
public:
    static Trajectory makeTrajectory(float xStart, float yStart, float xTarget, float yTarget, float duration, FISH_BEHAVIOR behavior);
    
    static Trajectory staticTrajectory(float,float);
private:
    TrajectoryFactory();

    static Trajectory makeRandom(float xStart, float yStart, float xTarget, float yTarget, float duration, FISH_BEHAVIOR behavior);

    static Trajectory makeLinear(float xStart, float yStart, float xTarget, float yTarget, float duration, FISH_BEHAVIOR behavior);

    static Trajectory makeSinusoidal(float xStart, float yStart, float xTarget, float yTarget, float duration, FISH_BEHAVIOR behavior);
};