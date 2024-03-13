#include <memory>
#include "menu.h"
#include "game.h"

int TetrisMenu::readHighscore() {
    std::ifstream file("highscore/highscores.txt");
    int highscore{0};
    int points;
    while (file >> points) {
        if (points > highscore) {
            highscore = points;
        }
    }
    file.close();
    return highscore;
}

void TetrisMenu::instructionSettings(sf::RenderWindow &window, sf::Sprite &instructionsSprite, sf::Text &backButton,
                                     sf::Font &font) {
    window.draw(instructionsSprite);
    window.draw(backButton);

    sf::Text instructionsTitleText("Instructions", font, 40);
    instructionsTitleText.setFillColor(sf::Color::White);
    instructionsTitleText.setPosition(230, 50);
    window.draw(instructionsTitleText);

    sf::Text instructionsContentText(
            "Use arrow keys to move and rotate the falling blocks.\n       Try to complete rows to score points! \n     Prevent the blocks from reaching the top!",
            font, 15);
    instructionsContentText.setFillColor(sf::Color::White);
    instructionsContentText.setPosition(50, 150);
    window.draw(instructionsContentText);
}

void TetrisMenu::gameSettings(sf::RenderWindow &window, bool &inGame, bool &inMenu) {
    TextureManager textureManager;
    Game tetris(textureManager);
    window.setVisible(false);
    tetris.start(textureManager);
    inGame = false;
    window.setVisible(true);
    inMenu = true;
}

void
TetrisMenu::handleMouseEvent(sf::RenderWindow &window, bool &inMenu, bool &inGame, bool &inInstructions, bool &quitGame,
                             sf::Text &playText, sf::Text &instructionsText, sf::Text &quitText, sf::Text &backButton,
                             sf::Clock &clock, sf::Color &defaultColor, sf::Color &hoverColor, bool &playHovered,
                             bool &instructionsHovered, bool &quitHovered, bool &backHovered, sf::Font &font,
                             sf::Color backDefaultColor, sf::Color backHoverColor) {
    sf::Event event{};
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (inMenu) {
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

                if (playText.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                    inMenu = false;
                    inGame = true;
                } else if (instructionsText.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                    inMenu = false;
                    inInstructions = true;
                } else if (quitText.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                    window.close();
                    quitGame = true;
                }
            }
        } else if (inInstructions) {
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

                if (backButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                    inInstructions = false;
                    inMenu = true;
                }
            }
        }
    }

    if (inMenu) {
        if (playText.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)))) {
            if (!playHovered) {
                playText.setFillColor(hoverColor);
                playHovered = true;
                clock.restart();
            }
        } else {
            playHovered = false;
            playText.setFillColor(defaultColor);
        }

        if (instructionsText.getGlobalBounds().contains(
                static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)))) {
            if (!instructionsHovered) {
                instructionsText.setFillColor(hoverColor);
                instructionsHovered = true;
                clock.restart();
            }
        } else {
            instructionsHovered = false;
            instructionsText.setFillColor(defaultColor);
        }

        if (quitText.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)))) {
            if (!quitHovered) {
                quitText.setFillColor(hoverColor);
                quitHovered = true;
                clock.restart();
            }
        } else {
            quitHovered = false;
            quitText.setFillColor(defaultColor);
        }
    } else if (inInstructions) {
        if (backButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)))) {
            if (!backHovered) {
                backButton.setFillColor(backHoverColor);
                backHovered = true;
                clock.restart();
            }
        } else {
            backHovered = false;
            backButton.setFillColor(backDefaultColor);
        }
    }
}


void TetrisMenu::generate() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Tetris");

    bool inMenu{true};
    bool inGame{false};
    bool inInstructions{false};
    bool quitGame{false};
    sf::Image icon;
    if (icon.loadFromFile("images/icon.ico")) {
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
    float animationTime{5};
    sf::Color defaultColor{sf::Color::White};
    sf::Color hoverColor{sf::Color::Red};
    bool playHovered{false};
    bool instructionsHovered{false};
    bool quitHovered{false};

    sf::Texture instructionsTexture;
    instructionsTexture.loadFromFile("images/instruction.jpg");
    sf::Sprite instructionsSprite;
    instructionsSprite.setTexture(instructionsTexture);
    instructionsSprite.setScale(static_cast<float>(window.getSize().x) / instructionsTexture.getSize().x,
                                static_cast<float>(window.getSize().y) / instructionsTexture.getSize().y);

    sf::Text backButton("Back", font, 40);
    backButton.setFillColor(sf::Color::White);
    backButton.setPosition(350, 500);
    sf::Color backDefaultColor{sf::Color::White};
    sf::Color backHoverColor{sf::Color::Red};
    bool backHovered{false};

    while (window.isOpen()) {


        sf::Time elapsed = clock.getElapsedTime();
        handleMouseEvent(window, inMenu, inGame, inInstructions, quitGame, playText, instructionsText, quitText,
                         backButton,
                         clock, defaultColor, hoverColor, playHovered, instructionsHovered, quitHovered, backHovered,
                         font, backDefaultColor, backHoverColor);

        window.clear();

        if (inMenu) {
            window.draw(happySprite);
            window.draw(titleText);
            window.draw(playText);
            window.draw(instructionsText);
            window.draw(quitText);
            window.draw(highscoreText);

        } else if (inInstructions) {
            instructionSettings(window, instructionsSprite, backButton, font);
        } else if (inGame) {
            gameSettings(window, inGame, inMenu);
        }

        window.display();

        if (quitGame)
            break;

        if (elapsed.asSeconds() > animationTime) {
            playText.setFillColor(defaultColor);
            instructionsText.setFillColor(defaultColor);
            quitText.setFillColor(defaultColor);
            backButton.setFillColor(backDefaultColor);
            clock.restart();
        }
    }
}

TetrisMenu::TetrisMenu() = default;;