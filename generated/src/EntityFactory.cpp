#include "../include/EntityFactory.h"

Coin* EntityFactory::createCoin(const sf::Texture& texture, float x, float y) {
    return new Coin(texture, x, y);
}

PiggyBank* EntityFactory::createPiggyBank(const sf::Texture& texture, float x, float y, int value) {
    return new PiggyBank(texture, x, y, value);
}

Laser* EntityFactory::createLaser(const sf::Texture& texture, float x, float y, int frameWidth, int frameHeight, int frames, float angle) {
    return new Laser(texture, x, y, frameWidth, frameHeight, frames, angle);
}
