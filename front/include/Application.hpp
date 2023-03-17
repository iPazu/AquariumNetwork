#pragma once

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>

#include <string>


class Application
{
public:
    Application();
    Application(const int&, const int&, std::string ="Aquarium");

    void run();
    void update(sf::Time);
    void handleEvents(sf::Event &);
    void render();

private:

    void loadTexture();

    sf::RenderWindow    mWindow;
    sf::Sprite          mSprite;
    sf::Texture         mTexture;

};