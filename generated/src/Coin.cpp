//
// Created by Vlad on 03-Dec-24.
//
#include <Coin.h>

Coin::Coin(const sf::Texture& texture_ref, float x, float y) : Object(texture_ref) {
    this->speed=-300.f;

    const int frameWidth = 40;
    const int frameHeight = 40;
    const int numFrames = 8;

    this->sprite.setTextureRect({0,0,frameWidth,frameHeight});

    this->sprite.setScale(1.f, 1.f);
    this->sprite.setOrigin(frameWidth/2.f, frameHeight/2.f);
    this->sprite.setPosition(x, y);

    std::vector<sf::IntRect> frames;
    for (int i = 0; i < numFrames; ++i) {
        frames.push_back({i * frameWidth, 0, frameWidth, frameHeight});
    }

this->animator = new Animate(this->sprite, frames, 0.08f); // 0.08 seconds per frame

}

Coin::~Coin() {
    delete this ->animator;
}


void Coin::update(float deltaTime) {
    this->sprite.move(this->speed*deltaTime, 0.f); // Move the coin
    this->animator->update(deltaTime); // Update animation
}

void Coin::render(sf::RenderTarget& target) const {
    target.draw(this->sprite);
}


float Coin::getY() const {
    return this->sprite.getPosition().y;
}

float Coin::getX() const {
    return this->sprite.getPosition().x;
}

float Coin::getWidth() const {
    return this->sprite.getGlobalBounds().width;
}
