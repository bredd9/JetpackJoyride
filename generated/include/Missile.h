//
// Created by Vlad on 05-Nov-24.
//

#ifndef MISSILE_H
#define MISSILE_H


#include <Object.h>
#include <Animate.h>


class Missile : public Object {
private:

    float speed;
    bool launched;
    float timer=0;


public:
    Missile(const sf::Texture& texture_ref);
    ~Missile() override;
    void update(float deltaTime)override;
    void render(sf::RenderTarget& target) const override;
    void launch(float yPosition);
    bool isLaunched() const;



};
#endif //MISSILE_H