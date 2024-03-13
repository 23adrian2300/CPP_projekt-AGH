#ifndef CONSTANS_H
#define CONSTANS_H

#include <array>
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;
constexpr int BLOCK_SIZE = 40;
constexpr int LINES = 20;
constexpr int COLS = 10;
constexpr int SQUARES = 4;
constexpr int IMG = 6;


struct BlockShape {
    vector<array<int, 2>> positions;
};
struct CoordinateShape {
    int x, y;
};
struct WindowConfig {
    sf::VideoMode videoMode;
    std::string title;
    sf::Vector2i position;
};

#endif //CONSTANS_H