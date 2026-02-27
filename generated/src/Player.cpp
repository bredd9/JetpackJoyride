//
// Created by Vlad on 03-Nov-24.
//
#include "../include/Player.h"


Player::Player() {
    gravity=350.0f;
    jetpackPower=-300.0f;
    isUsingJetpack=false;
    velocity = sf::Vector2f(0.0f, 0.0f);

    if (!this->texture.loadFromFile("../resources/JetpackWalking.png")) {
        std::cout << "Error loading texture" << std::endl;
    }

    this->sprite.setTexture(this->texture);
    this->sprite.setTextureRect({0, 0, 75, 100});
    this->sprite.setPosition(150, 791);

    // Set up animation frames (example)
    std::vector<sf::IntRect> frames = {
        {0, 0, 75, 100},   // Frame 1
        {75, 0, 75, 100},  // Frame 2
        {150, 0, 75, 100}, // Frame 3
    };

    // Create an animator for this player
    animator = new Animate(sprite, frames, 0.1f ); // 0.1f is the animation speed
}


Player::~Player() {
delete animator;
}

void Player::useJetpack(bool activate) {
    this->isUsingJetpack=activate;
}

void Player::update(float deltaTime) {
    //Using the Jetpack
    bool isInAir = (sprite.getPosition().y < 740 - sprite.getGlobalBounds().height);

    if (isInAir) {
        this->sprite.setTextureRect({225, 0, 75, 100});  // 4th stance
    } else {
        animator->update(deltaTime);
    }

    if(isUsingJetpack)
        velocity.y=jetpackPower;
    else velocity.y=gravity;
    sprite.move(0.f, velocity.y * deltaTime);

    //Not falling off the screen

    if(sprite.getPosition().y<0) {
        sprite.setPosition(sprite.getPosition().x,0);
        velocity.y=0;
    }
    else if(sprite.getPosition().y+sprite.getGlobalBounds().height > 740) {
        sprite.setPosition(sprite.getPosition().x, 740- sprite.getGlobalBounds().height);
        velocity.y=0;

    }



}

void Player::render(sf::RenderTarget &target) const {
    target.draw(this->sprite);
}



