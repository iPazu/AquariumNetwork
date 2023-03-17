#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(2500, 1900), "SFML works");

    sf::Texture texture;
    if (!texture.loadFromFile("../assets/angry.png")) {
        printf("File not loaded");
    }

    sf::Sprite sprite(texture);
    sprite.setScale(0.1f, 0.1f);



    sf::Clock clock;
    float speed = 100.0f;
    int direction = 1;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
                window.close();
        }

        float elapsedTime = clock.restart().asSeconds();
        sprite.move(speed * elapsedTime, speed * elapsedTime); // Move the sprite horizontally

        window.clear();
        window.draw(sprite);

        window.display();
    }

    return 0;
}