//
// Created by Vlad on 02-Dec-24.
//
#include <Object.h>

Object::Object(const sf::Texture& texture_ref)
    {
    this->sprite.setTexture(texture_ref);
    }

Object::~Object() {

}



