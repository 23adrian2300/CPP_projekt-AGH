#include "game.hpp"
#include "utils.cpp"
#include "renderer.cpp"
#include "eventhandler.cpp"
#include "move.cpp"
#include <fstream>
Game::Game()
{

    grid.resize(LINES);
    for (size_t i{}; i < grid.size(); ++i)
    {
        grid[i].resize(COLS);
    }

    WindowConfig windowConfig;
    windowConfig.videoMode = sf::VideoMode(400, 800);
    windowConfig.title = "Tetris";
    windowConfig.position = sf::Vector2i(800, 100);
    window = std::make_shared<sf::RenderWindow>(windowConfig.videoMode, windowConfig.title);
    window->setPosition(windowConfig.position);

    loadTextures();

    directionX = 0;
    points = 0;
    change = false;
    gameover = false;
    timer = 0;
    delay = 0.3;
    hue = 1;

    int number = rand() % IMG;
    for (size_t i = 0; i < SQUARES; ++i)
    {
        root1[i].x = COLS / 2 + block[number].positions[i][0] - 1;
        root1[i].y = block[number].positions[i][1];
    }

    showText();
}

void Game::loadTextures()
{
    tiles.loadFromFile("images/squares.png");
    sprite = std::make_shared<sf::Sprite>();
    sprite->setTexture(tiles);
    sprite->setTextureRect(sf::IntRect(0, 0, BLOCK_SIZE, BLOCK_SIZE));

    background.loadFromFile("images/background.png");
    backgroundSprite = std::make_shared<sf::Sprite>();
    backgroundSprite->setTexture(background);
}
void Game::setWindowIcon(const std::string &iconFilename)
{
    sf::Image icon;
    if (icon.loadFromFile(iconFilename))
    {
        window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    }
}

void Game::start()
{
    setWindowIcon("images/icon.ico");
    while (window->isOpen())
    {
        handleEvents();
        if (!gameover)
        {
            changePosition();
            rotateShape();
            moveShapeDown();
            setScore();
            directionX = 0;
            change = false;
            delay = 0.3;
        }
        render();
        if (gameover)
        {
            ofstream file;
            file.open("functions/highscores.txt", ios::app);
            file << points << endl;
            file.close();
            sf::sleep(sf::seconds(5));
            window->setVisible(false);
            gameover = false;
            break;
        }
    }
}
