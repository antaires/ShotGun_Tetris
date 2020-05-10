#include "Bullet.h"
#include "Constants.h"

#include <iostream>

Bullet::Bullet(float x, float y, int size): size(size)
{
  target.x = x;
  target.y = y;

  position.x = (float) WINDOW_WIDTH;
  position.y = (float) (WINDOW_HEIGHT / 2);

  velocity = target - position;
}

void Bullet::Update(float deltaTime)
{
  position.x = position.x + velocity.x * deltaTime;;
  position.y = position.y + velocity.y * deltaTime;
  // TODO: if position x or y offscreen, turn off bullet
}
