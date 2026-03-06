//
// Created by Vlad on 09-Jan-25.
//

#include "Collision.h"

// Funcția care "strânge" dreptunghiul spre centru
sf::FloatRect Collision::shrinkRect(const sf::FloatRect& rect, float scaleX, float scaleY) {
    float newWidth = rect.width * scaleX;
    float newHeight = rect.height * scaleY;
    float newLeft = rect.left + (rect.width - newWidth) / 2.f;
    float newTop = rect.top + (rect.height - newHeight) / 2.f;
    return sf::FloatRect(newLeft, newTop, newWidth, newHeight);
}

bool Collision::checkCollision(const sf::Sprite& sprite1, const sf::Sprite& sprite2,
                               float shrink1X, float shrink1Y,
                               float shrink2X, float shrink2Y) {
    // Micșorăm ambele cutii înainte să le verificăm
    sf::FloatRect bounds1 = shrinkRect(sprite1.getGlobalBounds(), shrink1X, shrink1Y);
    sf::FloatRect bounds2 = shrinkRect(sprite2.getGlobalBounds(), shrink2X, shrink2Y);

    // Check if the bounding boxes intersect
    return bounds1.intersects(bounds2);
}

bool Collision::checkRotatedCollision(const sf::Sprite& player, const sf::Sprite& laser,
                                      float pShrinkX, float pShrinkY,
                                      float lShrinkX, float lShrinkY) {
    // 1. Verificăm mai întâi cutiile globale (AABB) pentru optimizare
    if (!player.getGlobalBounds().intersects(laser.getGlobalBounds())) {
        return false;
    }

    // 2. Obținem matricea inversă a laserului
    sf::Transform inverseLaserTransform = laser.getInverseTransform();

    // 3. Tăiem din cutia texturii laserului (în spațiu local)
    sf::FloatRect laserLocalBounds = shrinkRect(laser.getLocalBounds(), lShrinkX, lShrinkY);

    // 4. Obținem și tăiem din cutia jucătorului (în spațiu global)
    sf::FloatRect pBounds = shrinkRect(player.getGlobalBounds(), pShrinkX, pShrinkY);

    // Creăm 5 puncte de test pentru jucător (colțurile și centrul din cutia micșorată)
    sf::Vector2f points[5] = {
        sf::Vector2f(pBounds.left, pBounds.top),
        sf::Vector2f(pBounds.left + pBounds.width, pBounds.top),
        sf::Vector2f(pBounds.left, pBounds.top + pBounds.height),
        sf::Vector2f(pBounds.left + pBounds.width, pBounds.top + pBounds.height),
        sf::Vector2f(pBounds.left + pBounds.width / 2.f, pBounds.top + pBounds.height / 2.f)
    };

    // 5. Transformăm fiecare punct în sistemul de coordonate al laserului
    for (int i = 0; i < 5; i++) {
        sf::Vector2f transformedPoint = inverseLaserTransform.transformPoint(points[i]);

        // Dacă un punct a intrat în hitbox-ul micșorat al laserului, avem coliziune!
        if (laserLocalBounds.contains(transformedPoint)) {
            return true;
        }
    }

    return false;
}