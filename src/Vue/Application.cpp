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
, mAquarium {0,2000,1000,1000, SpriteProperties[SPROP::AQUARIUM] }
, mConsole { 10, 10, 400, 500, 12 }
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
, mAquarium {0,2000,w,h, SpriteProperties[SPROP::AQUARIUM] }
, mConsole { 10, 10, 400, 500, 12 }
{
    std::string fish1 = "anim1";
    std::string fish2 = "anim2";
    mAquarium.addFish(fish1, FISH_TYPE::SHARK, 5, 5, 10, 10, 70, 50, 15.f);
    mAquarium.addFish(fish2, FISH_TYPE::BLUE, 50, 0, 5, 5, 50, 70, 7.f);
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
    // client.send("Vrei să pleci dar nu mă, nu mă iei\n"
    // "Nu mă, nu mă iei, nu mă, nu mă, nu mă iei\n"
    // "Chipul tău și dragostea din tei\n"
    // "Mi-amintesc de ochii tăi\n", 1024);

    char buffer[2048];
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
    mAquarium.update(dt);
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

        if (event.type == sf::Event::Resized)
        {
            // update the view to the new size of the window
            sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
            mWindow.setView(sf::View(visibleArea));
        }

        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::M && !mConsole.hasFocus())
        {
            mConsole.println("message from console");
        }

        auto mousePosition = sf::Mouse::getPosition(mWindow);

        if(event.type == sf::Event::MouseButtonReleased && mConsole.isPointIn(mousePosition.x, mousePosition.y))
        {
            std::cout << "toggling console" << std::endl;
            mConsole.toggle();
        }
        mConsole.handleEvent(event);
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
    mWindow.draw(mAquarium);
    mWindow.draw(mConsole);
    mWindow.display();
}

/**
 * @brief Returns position in window with given percentage.
 * 
 * @param percX width percentage
 * @param percY height percentage
 * @return Position in window
 */
sf::Vector2f Application::getPositionFromPerc(float percX, float percY) const
{
    auto windowSize = mWindow.getSize();

    return sf::Vector2f(windowSize.x * (percX/100.f), windowSize.y * (percY/100.f));
}