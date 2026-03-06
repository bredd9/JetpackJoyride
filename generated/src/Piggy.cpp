//
// Created by Vlad on 06-Mar-26.
//

#include "Piggy.h"


// Apelăm constructorul de bază Object(texture) pentru a seta textura automat
PiggyBank::PiggyBank(const sf::Texture& texture, float x, float y, int value)
    : Object(texture), coinValue(value), speed(300.f)
{
    // Variabila "sprite" este moștenită din Object, deci o putem folosi direct!
    this->sprite.setPosition(x, y);
    this->sprite.setScale(0.7f, 0.7f);
}

void PiggyBank::update(float deltaTime) {
    this->sprite.move(-this->speed * deltaTime, 0.f);
}

void PiggyBank::render(sf::RenderTarget& target) const {
    target.draw(this->sprite);
}

int PiggyBank::getValue() const {
    return this->coinValue;
}

float PiggyBank::getX() const {
    return this->sprite.getPosition().x;
}
