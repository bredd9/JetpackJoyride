//
// Created by Vlad on 09-Jan-25.
//

#ifndef COLLISION_H
#define COLLISION_H

#include <iostream>
#include <SFML/Graphics.hpp>

class Collision {
public:
    // Parametri opționali pentru a tăia marginile (1.0f = 100% din imagine, 0.5f = 50%)
    static bool checkCollision(const sf::Sprite& sprite1, const sf::Sprite& sprite2,
                               float shrink1X = 1.0f, float shrink1Y = 1.0f,
                               float shrink2X = 1.0f, float shrink2Y = 1.0f);

    // Coliziune pentru obiecte rotite, cu parametri de micșorare
    static bool checkRotatedCollision(const sf::Sprite& player, const sf::Sprite& laser,
                                      float pShrinkX = 1.0f, float pShrinkY = 1.0f,
                                      float lShrinkX = 1.0f, float lShrinkY = 1.0f);

private:
    // Funcție helper care face matematica de micșorare a cutiei
    static sf::FloatRect shrinkRect(const sf::FloatRect& rect, float scaleX, float scaleY);
};

#endif //COLLISION_H