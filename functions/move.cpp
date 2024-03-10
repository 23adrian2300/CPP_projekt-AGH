#include "game.hpp"
#include <cstdlib>

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
        for (auto & i : root2)
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