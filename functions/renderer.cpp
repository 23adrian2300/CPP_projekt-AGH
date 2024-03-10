#include "game.hpp"

void Game::render()
{
    window->clear(sf::Color::Black);
    window->draw(*backgroundSprite);

    for (size_t i = 0; i < LINES; ++i)
    {
        for (size_t j = 0; j < COLS; ++j)
        {
            if (grid[i][j] != 0)
            {
                sprite->setTextureRect(sf::IntRect(grid[i][j] * BLOCK_SIZE, 0, BLOCK_SIZE, BLOCK_SIZE));
                sprite->setPosition(j * BLOCK_SIZE, i * BLOCK_SIZE);
                window->draw(*sprite);
            }
        }
    }

    for (auto & i : root1)
    {
        sprite->setTextureRect(sf::IntRect(hue * BLOCK_SIZE, 0, BLOCK_SIZE, BLOCK_SIZE));
        sprite->setPosition(i.x * BLOCK_SIZE, i.y * BLOCK_SIZE);
        window->draw(*sprite);
    }

    window->draw(PointsShow);

    if (gameover)
    {
        window->draw(OverShow);
    }

    window->display();
}

void Game::showText()
{
    font.loadFromFile("font/font.ttf");
    PointsShow.setFont(font);
    PointsShow.setPosition(120, 10);
    PointsShow.setString("Points: " + to_string(points));
    PointsShow.setCharacterSize(30);
    PointsShow.setOutlineThickness(3);

    OverShow.setFont(font);
    OverShow.setPosition(75, 100);
    OverShow.setString("GAME OVER");
    OverShow.setCharacterSize(30);
    OverShow.setOutlineThickness(3);
}