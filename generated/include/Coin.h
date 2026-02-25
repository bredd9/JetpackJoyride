//
// Created by Vlad on 03-Dec-24.
//

#ifndef COINS_H
#define COINS_H

#include <Object.h>
#include <Animate.h>

class Coin : public Object {
private:
  float speed;           // Speed at which the coin moves
  sf::Vector2f position; // Position of the coin
  Animate *animator; // Animator for coin animation

public:
  Coin(const sf::Texture& texture_ref, float x, float y);
  ~Coin() override;

  // Override methods
  void update(float deltaTime) override;
  void render(sf::RenderTarget& target) const override;

  float getY() const;
  float getX() const;

  float getWidth() const;
};


#endif //COINS_H
