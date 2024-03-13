#include "textures.h"


void TextureManager::loadTextures() {
    tiles.loadFromFile("images/squares.png");
    sprite = std::make_shared<sf::Sprite>();
    sprite->setTexture(tiles);
    sprite->setTextureRect(sf::IntRect(0, 0, BLOCK_SIZE, BLOCK_SIZE));

    background.loadFromFile("images/background.png");
    backgroundSprite = std::make_shared<sf::Sprite>();
    backgroundSprite->setTexture(background);
}

const sf::Texture &TextureManager::getTiles() const {
    return tiles;
}

void TextureManager::setTiles(const sf::Texture &tiles) {
    TextureManager::tiles = tiles;
}

const sf::Texture &TextureManager::getBackground() const {
    return background;
}

void TextureManager::setBackground(const sf::Texture &background) {
    TextureManager::background = background;
}

const shared_ptr<sf::Sprite> &TextureManager::getSprite() const {
    return sprite;
}

void TextureManager::setSprite(const shared_ptr<sf::Sprite> &sprite) {
    TextureManager::sprite = sprite;
}

const shared_ptr<sf::Sprite> &TextureManager::getBackgroundSprite() const {
    return backgroundSprite;
}

void TextureManager::setBackgroundSprite(const shared_ptr<sf::Sprite> &backgroundSprite) {
    TextureManager::backgroundSprite = backgroundSprite;
}

