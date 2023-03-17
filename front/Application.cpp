#include "include/Application.hpp"

Application::Application()
: mWindow{sf::VideoMode().getDesktopMode(), "Aquarium", sf::Style::Fullscreen}
{
    loadTexture();
    mSprite.setTexture(mTexture);
}

Application::Application(const int& w, const int& h, std::string winName)
: mWindow{ sf::VideoMode(w,h), winName }
{
    loadTexture();
    mSprite.setTexture(mTexture);
}

void Application::run()
{
    sf::Clock clock {};
	sf::Time elapsed = sf::Time::Zero;

    

    while (mWindow.isOpen())
    {
        sf::Event event;
        handleEvents(event);
        elapsed = clock.restart();
        update(elapsed);
        render();
       
    }
}

void Application::update(sf::Time dt)
{
    float speed = 100.0f;
    mSprite.move(speed * dt.asSeconds(), speed * dt.asSeconds());
}

void Application::handleEvents(sf::Event& event)
{
    while (mWindow.pollEvent(event))
    {

        if (event.type == sf::Event::Closed)
            mWindow.close();
    }
}

void Application::render()
{
     mWindow.clear();
    mWindow.draw(mSprite);
    mWindow.display();
}

void Application::loadTexture()
{
    if (!mTexture.loadFromFile("../assets/angry.png")) {
        printf("File not loaded");
    }
}