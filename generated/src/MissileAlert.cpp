//
// Created by Vlad on 06-Nov-24.
//
#include <../include/MissileAlert.h>
#include <../include/Player.h>

MissileAlert::MissileAlert(const sf::Texture& texture_ref, const Player* player) : Object(texture_ref), playerRef(player) {
    active = false;
    alertDuration = 4.0f;
    this->sprite.setTextureRect({0, 0, 100, 100});

    // Scaling sprite
    this->sprite.scale(0.8f, 0.8f);

    // Define animation frames
    std::vector<sf::IntRect> frames = {
        {0, 0, 100, 100},   // Frame 1
        {100, 0, 100, 100}, // Frame 2
    };

    // Initialize animator
    animator = new Animate(sprite, frames, 0.2f); // Animation speed: 0.2 seconds per frame
}

MissileAlert::~MissileAlert() = default;


float MissileAlert::getY() const {
    return sprite.getPosition().y;
}

void MissileAlert::alert() {
    active = true;
    timer.restart();

}

bool MissileAlert::isAlerting() const {
    return active;
}


void MissileAlert::update(float deltaTime){
    if(!active) return;
    if(timer.getElapsedTime().asSeconds() >= alertDuration) {
        active = false;
    }
    else {
        if(playerRef) {
            float currentPlayerY=this->playerRef->getSprite().getPosition().y;
            this->sprite.setPosition(1200-this->sprite.getGlobalBounds().width,currentPlayerY); // Follow player
            animator->update(deltaTime);
        }
    }
}




void MissileAlert::render(sf::RenderTarget &target) const {
    if(isAlerting()) {
        target.draw(this->sprite);
    }
}

