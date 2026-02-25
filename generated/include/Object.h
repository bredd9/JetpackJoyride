//
// Created by Vlad on 02-Dec-24.
//

#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <SFML/Graphics.hpp>

class Object{

protected:
    sf::Sprite sprite;

public:
    Object(const sf::Texture& texture_ref);
    virtual ~Object();
    virtual void update(float deltaTime)=0;
    virtual void render(sf::RenderTarget& target)const=0;
    const sf::Sprite& getSprite() const { return this->sprite; }
};

#endif //OBJECT_H
