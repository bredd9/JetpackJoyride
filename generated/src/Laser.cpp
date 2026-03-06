//
// Created by Vlad on 06-Mar-26.
//

#include "Laser.h"

// Din nou, apelăm Object(texture)
Laser::Laser(const sf::Texture& texture, float x, float y, int fWidth, int fHeight, int frames, float angle)
    : Object(texture), speed(300.f), frameWidth(fWidth), frameHeight(fHeight), totalFrames(frames)
{
    this->currentFrameRect = sf::IntRect(0, 0, this->frameWidth, this->frameHeight);
    this->sprite.setTextureRect(this->currentFrameRect);

    // 1. SETĂM ORIGINEA ÎN CENTRUL IMAGINII (jumătate din lățime și înălțime)
    this->sprite.setOrigin(this->frameWidth / 2.f, this->frameHeight / 2.f);

    // 2. Setăm poziția și unghiul
    this->sprite.setPosition(x, y);
    this->sprite.setRotation(angle); // <--- Aici se rotește laserul!

    this->animationTimer = 0.f;
    this->animationTimerMax = 0.1f;
}

void Laser::update(float deltaTime) {
    // 1. Mutăm laserul spre stânga
    this->sprite.move(-this->speed * deltaTime, 0.f);

    // 2. Animația
    this->animationTimer += deltaTime;
    if (this->animationTimer >= this->animationTimerMax) {
        this->animationTimer = 0.f;

        // Trecem la cadrul următor
        this->currentFrameRect.left += this->frameWidth;

        // Dacă am ajuns la finalul imaginii, o luăm de la capăt (buclă)
        if (this->currentFrameRect.left >= this->frameWidth * this->totalFrames) {
            this->currentFrameRect.left = 0;
        }

        this->sprite.setTextureRect(this->currentFrameRect);
    }
}

void Laser::render(sf::RenderTarget& target) const {
    target.draw(this->sprite);
}

float Laser::getX() const {
    return this->sprite.getPosition().x;
}