#pragma once

#include <fstream>
#include <memory>
#include <SFML/Graphics.hpp>


class TetrisMenu {

public:
    TetrisMenu();

    static int readHighscore();

    static void generate();

    static void
    instructionSettings(sf::RenderWindow &window, sf::Sprite &instructionsSprite, sf::Text &backButton, sf::Font &font);

    static void
    handleMouseEvent(sf::RenderWindow &window, bool &inMenu, bool &inGame, bool &inInstructions, bool &quitGame,
                     sf::Text &playText, sf::Text &instructionsText, sf::Text &quitText, sf::Text &backButton,
                     sf::Clock &clock, sf::Color &defaultColor, sf::Color &hoverColor, bool &playHovered,
                     bool &instructionsHovered, bool &quitHovered, bool &backHovered, sf::Font &font,
                     sf::Color backDefaultColor, sf::Color backHoverColor);

    static void gameSettings(sf::RenderWindow &window, bool &inGame, bool &inMenu);
};
