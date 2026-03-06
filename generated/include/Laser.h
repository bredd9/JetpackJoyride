//
// Created by Vlad on 06-Mar-26.
//

#ifndef LASER_H
#define LASER_H

#include "Object.h"

class Laser : public Object {
private:
    float speed;

    sf::IntRect currentFrameRect;
    float animationTimer;
    float animationTimerMax;
    int frameWidth;
    int frameHeight;
    int totalFrames;

public:
    // În Laser.h, modifică doar linia constructorului:
    Laser(const sf::Texture& texture, float x, float y, int fWidth, int fHeight, int frames, float angle);
    ~Laser() override = default;

    void update(float deltaTime) override;
    void render(sf::RenderTarget& target) const override;

    float getX() const;
};

#endif //LASER_H
