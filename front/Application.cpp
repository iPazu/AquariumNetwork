/**
 * @file Application.cpp
 * @author Nicolas Gry(grybouilli@outlook.fr)
 * @brief Application class implementation
 * @version 0.1
 * @date 2023-03-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "include/Application.hpp"
#include "include/TextureData.hpp"


/**
 * @brief Construct a new Application object
 * 
 */
Application::Application()
: mWindow{ sf::VideoMode().getDesktopMode(), "Aquarium", sf::Style::Fullscreen }
, mSprite {SpriteProperties[SPROP::ANGRY]}
{

}

/**
 * @brief Construct a new Application object
 * 
 * This constructor allows you to set the width, height and title of the window in which the app runs.
 * @param w The window width
 * @param h The window height
 * @param winName The window name
 */
Application::Application(const int& w, const int& h, std::string winName)
: mWindow{ sf::VideoMode(w,h), winName }
, mSprite {SpriteProperties[SPROP::ANGRY]}
{
}

/**
 * @brief The app main loop.
 * 
 * This function contains the main of the app and does the entire job of handling events, updating entities and rendering them.
 * 
 */
void Application::run()
{
    sf::Clock clock {};
	sf::Time elapsed = sf::Time::Zero;

    

    while (mWindow.isOpen())
    {
        handleEvents();
        elapsed = clock.restart();
        update(elapsed);
        render();
       
    }
}

/**
 * @brief Update function of the app.
 * 
 * Updates the entities attached to the Application class.
 * 
 * @param dt Elapsed time since last call to the update function.
 */
void Application::update(sf::Time dt)
{
    float speed = 100.0f;
    mSprite.move(speed * dt.asSeconds(), speed * dt.asSeconds());
}


/**
 * @brief Event handling function.
 * 
 * Is in charge of processing the inputs triggered in the application graphic window.
 */
void Application::handleEvents()
{
    sf::Event event;

    while (mWindow.pollEvent(event))
    {

        if (event.type == sf::Event::Closed)
            mWindow.close();
    }
}

/**
 * @brief Render function
 * 
 * Draw all the elements attached to the app in the app grpahic window.
 * 
 */
void Application::render()
{
     mWindow.clear();
    mWindow.draw(mSprite);
    mWindow.display();
}
