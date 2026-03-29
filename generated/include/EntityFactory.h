#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#include <Coin.h>
#include <Piggy.h>
#include <Laser.h>

class EntityFactory {
public:
    static Coin* createCoin(const sf::Texture& texture, float x, float y);
    static PiggyBank* createPiggyBank(const sf::Texture& texture, float x, float y, int value);
    static Laser* createLaser(const sf::Texture& texture, float x, float y, int frameWidth, int frameHeight, int frames, float angle);
};

#endif // ENTITYFACTORY_H
