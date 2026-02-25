//
// Created by Vlad on 03-Nov-24.
//

#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <Animate.h>

class Player {

private:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Vector2f velocity;
    Animate* animator;
    float gravity;
    float jetpackPower;
    bool isUsingJetpack;





public:
    Player();
    ~Player();
    void update(float deltaTime);
    void render(sf::RenderTarget& target) const;
    void useJetpack(bool activate);
    const sf::Sprite& getSprite() const { return sprite; }



};
#endif //PLAYER_H
