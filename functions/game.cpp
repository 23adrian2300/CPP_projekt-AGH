#include "game.h"
#include <fstream>

Game::Game(TextureManager &textureManager)
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
    textureManager.loadTextures();

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

void Game::start(TextureManager &textureManager)
{
    sf::Image icon;
    if (icon.loadFromFile("images/icon.ico"))
    {
        window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    }

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
        render(textureManager);
        if (gameover)
        {
            ofstream file;
            file.open("highscore/highscores.txt", ios::app);
            file << points << endl;
            file.close();
            sf::sleep(sf::seconds(2));
            window->setVisible(false);
            gameover = false;
            break;
        }
    }
}

void Game::moveShapeDown()
{
    if (timer <= delay)
        return;

    for (size_t i = 0; i < SQUARES; ++i)
    {
        root2[i] = root1[i];
        ++root1[i].y;
    }

    if (limit())
    {
        for (auto &i : root2)
        {
            grid[i.y][i.x] = hue;
        }

        hue = rand() % IMG + 1;
        int number{rand() % IMG};

        for (size_t i = 0; i < SQUARES; ++i)
        {
            root1[i].x = COLS / 2 + block[number].positions[i][0] - 1;
            root1[i].y = block[number].positions[i][1];
        }
    }

    timer = 0;

    delay -= 0.005;

    if (delay < 0.1)
        delay = 0.1;
}

void Game::render(TextureManager &textureManager)
{

    window->clear(sf::Color::Black);
    window->draw(*textureManager.getBackgroundSprite());

    for (size_t i = 0; i < LINES; ++i)
    {
        for (size_t j = 0; j < COLS; ++j)
        {
            if (grid[i][j] != 0)
            {
                textureManager.getSprite()->setTextureRect(
                    sf::IntRect(grid[i][j] * BLOCK_SIZE, 0, BLOCK_SIZE, BLOCK_SIZE));
                textureManager.getSprite()->setPosition(j * BLOCK_SIZE, i * BLOCK_SIZE);
                window->draw(*textureManager.getSprite());
            }
        }
    }

    for (auto &i : root1)
    {
        textureManager.getSprite()->setTextureRect(sf::IntRect(hue * BLOCK_SIZE, 0, BLOCK_SIZE, BLOCK_SIZE));
        textureManager.getSprite()->setPosition(i.x * BLOCK_SIZE, i.y * BLOCK_SIZE);
        window->draw(*textureManager.getSprite());
    }

    window->draw(PointsShow);

    if (gameover)
    {
        window->draw(OverShow);
    }

    window->display();
}

void Game::rotateShape()
{
    if (change)
    {
        CoordinateShape center = root1[1];
        for (auto &i : root1)
        {
            const int x{i.y - center.y};
            const int y{i.x - center.x};

            i.x = center.x - x;
            i.y = center.y + y;
        }

        if (limit())
        {
            for (size_t i = 0; i < SQUARES; ++i)
            {
                root1[i] = root2[i];
            }
        }
    }
}

void Game::changePosition()
{
    for (size_t i = 0; i < SQUARES; ++i)
    {
        root2[i] = root1[i];
        root1[i].x += directionX;
    }

    if (limit())
    {
        for (size_t i = 0; i < SQUARES; ++i)
        {
            root1[i] = root2[i];
        }
    }
}

bool Game::limit()
{
    for (auto &i : root1)
    {
        if (i.x < 0 ||
            i.x >= COLS ||
            i.y >= LINES ||
            grid[i.y][i.x] != 0)
        {
            return true;
        }
    }
    return false;
}

void Game::setScore()
{
    int match{LINES - 1};
    for (int i = match; i >= 1; --i)
    {
        int sum{0};
        for (size_t j = 0; j < COLS; ++j)
        {
            if (grid[i][j] != 0)
            {
                if (i == 1)
                {
                    gameover = true;
                }
                ++sum;
            }
            grid[match][j] = grid[i][j];
        }
        if (sum < COLS)
        {
            --match;
        }
        else
        {
            PointsShow.setString("Points: " + std::to_string(++points));
        }
    }
}

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