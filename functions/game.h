#pragma once

#include <SFML/Graphics.hpp>
#include "constans.h"
#include <array>
#include <memory>
#include <vector>
#include "textures.h"

class TextureManager;

class Game {
    vector<vector<int>> grid;

    vector<BlockShape> block = {
            {{{0, 1}, {0, 2}, {0, 3}, {0, 4}}},
            {{{0, 1}, {1, 1}, {1, 0}, {2, 0}}},
            {{{0, 0}, {0, 1}, {1, 1}, {1, 2}}},
            {{{0, 1}, {1, 0}, {1, 1}, {1, 2}}},
            {{{0, 0}, {1, 0}, {2, 0}, {2, 1}}},
            {{{0, 2}, {1, 0}, {1, 1}, {1, 2}}},
            {{{0, 0}, {0, 1}, {1, 0}, {1, 1}}}};

    CoordinateShape root1[SQUARES]{};
    CoordinateShape root2[SQUARES]{};
    shared_ptr<sf::RenderWindow> window;
    sf::Clock clock;
    sf::Font font;
    sf::Text PointsShow;
    sf::Text OverShow;
    int directionX;
    int hue;
    int points;
    bool change;
    bool gameover;
    float timer;
    float delay;

private:
    void handleEvents();

    void render(TextureManager &textureManager);

    void moveShapeDown();

    void rotateShape();

    void changePosition();

    bool limit();

    void setScore();


public:
    explicit Game(TextureManager &textureManager);

    void start(TextureManager &textureManager);
};
