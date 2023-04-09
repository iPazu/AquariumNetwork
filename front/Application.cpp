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
#include "include/ClientController.hpp"
#include "include/IOUtils.hpp"

/**
 * @brief Construct a new Application object
 * 
 */
Application::Application()
: mWindow{ sf::VideoMode().getDesktopMode(), "Aquarium", sf::Style::Fullscreen }
//, mSprite {SpriteProperties[SPROP::ANGRY]}
, mButton {100, 100, SpriteProperties[SPROP::BUTTON]}
, mFish {0,0, 100, 100, 2}
{
    UIElement::Callback func = [] (std::string) { std::cout << " clicked !" << std::endl; return "";};
    mButton.setCallback(func);

    mFish.setScale(.5,.5);
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
//, mSprite {SpriteProperties[SPROP::ANGRY]}
, mButton {100, 100, SpriteProperties[SPROP::BUTTON]}
, mFish {100, 100, 500, 500, 5}
{
    UIElement::Callback func = [] (std::string) { std::cout << " clicked !" << std::endl; return "";};
    mButton.setCallback(func);
    mFish.setSize(100,100);

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

    //Connect to the server
    ClientController client;
    client.connect("colette.julien-chabrier.fr",3000);

    //Perform a simple operation
    client.send("Vrei să pleci dar nu mă, nu mă iei\n"
    "Nu mă, nu mă iei, nu mă, nu mă, nu mă iei\n"
    "Chipul tău și dragostea din tei\n"
    "Mi-amintesc de ochii tăi\n", 1024);

    char buffer[1024];
    client.receive(buffer, 1024);
    printf("Received: %s\n", buffer);


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
   // float speed = 100.0f;
   // mSprite.move(speed * dt.asSeconds(), speed * dt.asSeconds());
   mFish.updateCurrent(dt);
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
        if(event.type == sf::Event::MouseButtonPressed)
        {
            auto mousePos = sf::Mouse::getPosition(mWindow);
            if(mButton.isOnButton(mousePos.x, mousePos.y))
            {
                std::cout << "polling mouse event..." << std::endl;
                mButton.toggle();
            }
        }

        if(event.type == sf::Event::MouseButtonReleased)
        {
            if(mButton.isToggled())
            {
                mButton.deselect();
            }
        }
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
    mWindow.draw(mButton);
    mWindow.draw(mFish);
    mWindow.display();
}
