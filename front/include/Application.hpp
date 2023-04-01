#pragma once

//! \file Application.h
//! \brief Header file for the Application class.

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>
#include "SpriteNode.hpp"
#include "Button.hpp"

#include <string>

/** \class Application 
 * \brief Base class for the application.
 * 
 * This class holds the main objects to be manipulated through the UI, and is in charge of updating and rendering them. It also handles user events and acts on entities in consequence.
 * 
 */
class Application
{
public:
    Application();
    Application(const int&, const int&, std::string ="Aquarium");  
    
    void run();
    void update(sf::Time);
    void handleEvents();
    void render();

private:

    sf::RenderWindow    mWindow;
    //SpriteNode          mSprite;
    Button              mButton;
};