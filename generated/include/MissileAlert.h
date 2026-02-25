//
// Created by Vlad on 06-Nov-24.
//

#ifndef MISSILEALERT_H
#define MISSILEALERT_H

#include <Object.h>
#include <Animate.h>

class Player;

class MissileAlert : public Object {
private:

    bool active;
    sf::Clock timer;
    float alertDuration;
    Animate *animator;
    const Player* playerRef;
public:

    MissileAlert(const sf::Texture& texture_ref, const Player* player);
    ~MissileAlert() override;
    void update(float deltaTime) override;
    float getY()const;
    void render(sf::RenderTarget& target) const override;
    void alert();
    bool isAlerting()const;

};





#endif //MISSILEALERT_H