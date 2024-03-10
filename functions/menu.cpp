#include "game.hpp"
#include <time.h>
#include <fstream>
#include <memory>

class TetrisGame
{
public:
    void run()
    {
        std::srand(static_cast<int>(std::time(0)));

        game = std::make_shared<Game>();
        game->start();
    }

private:
    std::shared_ptr<Game> game;
};

int readHighscore()
{
    std::ifstream file("highscores.txt");
    int highscore = 0;
    int points;
    while (file >> points)
    {
        if (points > highscore)
        {
            highscore = points;
        }
    }
    file.close();
    return highscore;
}

class TetrisMenu
{
public:
    void generate()
    {
        sf::RenderWindow window(sf::VideoMode(800, 600), "Tetris");

        bool inMenu = true;
        bool inGame = false;
        bool inInstructions = false;
        bool quitGame = false;
        sf::Image icon;
        if (icon.loadFromFile("images/icon.ico"))
        {
            window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
        }
        sf::Font font;
        font.loadFromFile("font/font.ttf");

        sf::Texture happyTexture;
        happyTexture.loadFromFile("images/happy.jpg");
        sf::Sprite happySprite;
        happySprite.setTexture(happyTexture);
        happySprite.setScale(static_cast<float>(window.getSize().x) / happyTexture.getSize().x,
                             static_cast<float>(window.getSize().y) / happyTexture.getSize().y);

        sf::Text titleText("Tetris", font, 60);
        titleText.setFillColor(sf::Color::White);
        titleText.setPosition(280, 200);

        sf::Text playText("Play", font, 40);
        playText.setFillColor(sf::Color::White);
        playText.setPosition(350, 350);

        sf::Text instructionsText("How to Play", font, 40);
        instructionsText.setFillColor(sf::Color::White);
        instructionsText.setPosition(220, 400);

        sf::Text quitText("Quit", font, 40);
        quitText.setFillColor(sf::Color::White);
        quitText.setPosition(350, 450);

        sf::Text highscoreText("Most points: " + std::to_string(readHighscore()), font, 20);
        highscoreText.setFillColor(sf::Color::White);
        highscoreText.setPosition(10, 10);

        sf::Clock clock;
        float animationTime = 5;
        sf::Color defaultColor = sf::Color::White;
        sf::Color hoverColor = sf::Color::Red;
        bool playHovered = false;
        bool instructionsHovered = false;
        bool quitHovered = false;

        sf::Texture instructionsTexture;
        instructionsTexture.loadFromFile("images/instruction.jpg");
        sf::Sprite instructionsSprite;
        instructionsSprite.setTexture(instructionsTexture);
        instructionsSprite.setScale(static_cast<float>(window.getSize().x) / instructionsTexture.getSize().x,
                                    static_cast<float>(window.getSize().y) / instructionsTexture.getSize().y);

        sf::Text backButton("Back", font, 40);
        backButton.setFillColor(sf::Color::White);
        backButton.setPosition(350, 500);
        sf::Color backDefaultColor = sf::Color::White;
        sf::Color backHoverColor = sf::Color::Red;
        bool backHovered = false;

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();

                if (inMenu)
                {
                    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
                    {
                        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

                        if (playText.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                        {
                            inMenu = false;
                            inGame = true;
                        }
                        else if (instructionsText.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                        {
                            inMenu = false;
                            inInstructions = true;
                        }
                        else if (quitText.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                        {
                            window.close();
                            quitGame = true;
                        }
                    }
                }
                else if (inInstructions)
                {
                    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
                    {
                        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

                        if (backButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                        {
                            inInstructions = false;
                            inMenu = true;
                        }
                    }
                }
            }

            sf::Time elapsed = clock.getElapsedTime();

            if (inMenu)
            {
                if (playText.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))))
                {
                    if (!playHovered)
                    {
                        playText.setFillColor(hoverColor);
                        playHovered = true;
                        clock.restart();
                    }
                }
                else
                {
                    playHovered = false;
                    playText.setFillColor(defaultColor);
                }

                if (instructionsText.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))))
                {
                    if (!instructionsHovered)
                    {
                        instructionsText.setFillColor(hoverColor);
                        instructionsHovered = true;
                        clock.restart();
                    }
                }
                else
                {
                    instructionsHovered = false;
                    instructionsText.setFillColor(defaultColor);
                }

                if (quitText.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))))
                {
                    if (!quitHovered)
                    {
                        quitText.setFillColor(hoverColor);
                        quitHovered = true;
                        clock.restart();
                    }
                }
                else
                {
                    quitHovered = false;
                    quitText.setFillColor(defaultColor);
                }
            }
            else if (inInstructions)
            {
                if (backButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))))
                {
                    if (!backHovered)
                    {
                        backButton.setFillColor(backHoverColor);
                        backHovered = true;
                        clock.restart();
                    }
                }
                else
                {
                    backHovered = false;
                    backButton.setFillColor(backDefaultColor);
                }
            }

            window.clear();

            if (inMenu)
            {
                window.draw(happySprite);
                window.draw(titleText);
                window.draw(playText);
                window.draw(instructionsText);
                window.draw(quitText);
                window.draw(highscoreText);
            }
            else if (inInstructions)
            {
                window.draw(instructionsSprite);
                window.draw(backButton);

                sf::Text instructionsTitleText("Instructions", font, 40);
                instructionsTitleText.setFillColor(sf::Color::White);
                instructionsTitleText.setPosition(230, 50);
                window.draw(instructionsTitleText);

                sf::Text instructionsContentText("Use arrow keys to move and rotate the falling blocks.\n       Try to complete rows to score points! \n     Prevent the blocks from reaching the top!", font, 15);
                instructionsContentText.setFillColor(sf::Color::White);
                instructionsContentText.setPosition(50, 150);
                window.draw(instructionsContentText);
            }
            else if (inGame)
            {
                TetrisGame tetris;
                tetris.run();
                inGame = false;
                inMenu = true;
            }

            window.display();

            if (quitGame)
                break;

            if (elapsed.asSeconds() > animationTime)
            {
                playText.setFillColor(defaultColor);
                instructionsText.setFillColor(defaultColor);
                quitText.setFillColor(defaultColor);
                backButton.setFillColor(backDefaultColor);
                clock.restart();
            }
        }
    }
};