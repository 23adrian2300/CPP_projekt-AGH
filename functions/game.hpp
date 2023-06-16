#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
using namespace std;
#define BLOCK_SIZE 40
#define LINES 20
#define COLS 10
#define SQUARES 4
#define IMG 6

struct BlockShape
{
    vector<array<int, 2>> positions;
};
struct CoordinateShape
{
    int x, y;
};
struct WindowConfig
{
    sf::VideoMode videoMode;
    std::string title;
    sf::Vector2i position;
};

class Game
{
    vector<vector<int>> grid;

    vector<BlockShape> block = {
        {{{0, 1}, {0, 2}, {0, 3}, {0, 4}}},
        {{{0, 1}, {1, 1}, {1, 0}, {2, 0}}},
        {{{0, 0}, {0, 1}, {1, 1}, {1, 2}}},
        {{{0, 1}, {1, 0}, {1, 1}, {1, 2}}},
        {{{0, 0}, {1, 0}, {2, 0}, {2, 1}}},
        {{{0, 2}, {1, 0}, {1, 1}, {1, 2}}},
        {{{0, 0}, {0, 1}, {1, 0}, {1, 1}}}};

    CoordinateShape root1[SQUARES];
    CoordinateShape root2[SQUARES];
    shared_ptr<sf::RenderWindow> window;
    sf::Texture tiles, background;
    shared_ptr<sf::Sprite> sprite;
    shared_ptr<sf::Sprite> backgroundSprite;
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

protected:
    void handleEvents();
    void loadTextures();
    void render();
    void moveShapeDown();
    void rotateShape();
    void changePosition();
    bool limit();
    void setScore();
    void showText();
    void setWindowIcon(const std::string &iconFilename);

public:
    Game();
    void start();
};
