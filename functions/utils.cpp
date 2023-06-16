#include "game.hpp"

void Game::rotateShape()
{
    if (change)
    {
        CoordinateShape center = root1[1];
        for (size_t i = 0; i < SQUARES; ++i)
        {
            int x = root1[i].y - center.y;
            int y = root1[i].x - center.x;

            root1[i].x = center.x - x;
            root1[i].y = center.y + y;
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
    for (size_t i = 0; i < SQUARES; ++i)
    {
        if (root1[i].x < 0 ||
            root1[i].x >= COLS ||
            root1[i].y >= LINES ||
            grid[root1[i].y][root1[i].x] != 0)
        {
            return true;
        }
    }
    return false;
}

void Game::setScore()
{
    int match = LINES - 1;
    for (int i = match; i >= 1; --i)
    {
        int sum = 0;
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