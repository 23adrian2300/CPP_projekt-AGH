#ifndef TEXTURES_H
#define TEXTURES_H

#include <SFML/Graphics.hpp>
#include "constans.h"
#include "game.h"
#include <memory>
#include <fstream>


class TextureManager {
    sf::Texture tiles, background;
    shared_ptr<sf::Sprite> sprite;
public:


    const sf::Texture &getTiles() const;

    void setTiles(const sf::Texture &tiles);

    const sf::Texture &getBackground() const;

    void setBackground(const sf::Texture &background);

    const shared_ptr<sf::Sprite> &getSprite() const;

    void setSprite(const shared_ptr<sf::Sprite> &sprite);

    const shared_ptr<sf::Sprite> &getBackgroundSprite() const;

    void setBackgroundSprite(const shared_ptr<sf::Sprite> &backgroundSprite);

    shared_ptr<sf::Sprite> backgroundSprite;

    void loadTextures();

};

#endif //TEXTURES_H
