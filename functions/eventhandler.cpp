#include "game.hpp"

void Game::handleEvents()
{
    float time = clock.getElapsedTime().asSeconds();
    clock.restart();
    timer += time;
    auto event = make_shared<sf::Event>();
    while (window->pollEvent(*event))
    {
        if (event->type == sf::Event::Closed)
        {
            window->close();
        }

        if (event->type == sf::Event::KeyPressed)
        {
            switch (event->key.code)
            {
            case sf::Keyboard::Up:
                change = true;
                break;
            case sf::Keyboard::Right:
                ++directionX;
                break;
            case sf::Keyboard::Left:
                --directionX;
                break;
            default:
                break;
            }
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        delay = 0.03;
    }
}