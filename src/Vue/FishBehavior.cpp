#include "include/FishBehavior.hpp"
#include "include/GeomUtils.hpp"
#include <cmath>
#include <SFML/Graphics/Transform.hpp>
Trajectory TrajectoryFactory::makeTrajectory(float xStart, float yStart, float xTarget, float yTarget, float duration, FISH_BEHAVIOR behavior)
{
    switch (behavior)
    {
    case FISH_BEHAVIOR::RANDOM:
        return makeRandom(xStart, yStart, xTarget, yTarget, duration, behavior);
        break;
    case FISH_BEHAVIOR::LINEAR:
        return makeLinear(xStart, yStart, xTarget, yTarget, duration, behavior);
        break;
    case FISH_BEHAVIOR::SINUSOIDAL:
        return makeSinusoidal(xStart, yStart, xTarget, yTarget, duration, behavior);
        break;
    default:
        return staticTrajectory(xStart, yStart);
        break;
    }
    return staticTrajectory(xStart, yStart);
}

Trajectory TrajectoryFactory::staticTrajectory(float posx, float posy)
{
    return [=] (sf::Time) { return sf::Vector2f(posx,posy); };
}


TrajectoryFactory::TrajectoryFactory()
{

}

Trajectory TrajectoryFactory::makeRandom(float xStart, float yStart, float xTarget, float yTarget, float duration, FISH_BEHAVIOR behavior)
{
    return Trajectory();
}

Trajectory TrajectoryFactory::makeLinear(float xStart, float yStart, float xTarget, float yTarget, float duration, FISH_BEHAVIOR behavior)
{
    sf::Vector2f direction { xTarget-xStart, yTarget-yStart };
    Trajectory linear = [=](sf::Time dt)
    {
        return (dt.asSeconds()/duration) * direction;
    };
    return linear;
}

Trajectory TrajectoryFactory::makeSinusoidal(float xStart, float yStart, float xTarget, float yTarget, float duration, FISH_BEHAVIOR behavior)
{
    float d { distance(xStart, yStart, xTarget, yTarget)};
    int m { 2 }; // number of period during trajectory
    float amp { 50.f };
    float f { 2.f * m * (float)M_PI / d };
    float phi { std::asin(amp/yStart) - xStart * f };
    float angle { vectorAngle(sf::Vector2f{xTarget-xStart, yTarget-yStart}) };
    sf::Transform rotation{ };
    rotation.rotate(angle);

    Trajectory sinusoidal = [=](sf::Time dt) 
    {
        float x = dt.asSeconds() * d / duration;
        float y = amp * std::sin(f*x+phi);
        return rotation.transformPoint(x,y);
    };
    
    return sinusoidal;
}