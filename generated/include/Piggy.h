//
// Created by Vlad on 06-Mar-26.
//

#ifndef PIGGY_H
#define PIGGY_H

#include "Object.h"

class PiggyBank : public Object {
private:
    int coinValue;
    float speed;

public:
    PiggyBank(const sf::Texture& texture, float x, float y, int value = 50);
    ~PiggyBank() override = default;

    void update(float deltaTime) override;
    void render(sf::RenderTarget& target) const override;

    int getValue() const;
    float getX() const;
};






#endif //PIGGY_H
