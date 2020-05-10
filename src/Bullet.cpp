#include "Bullet.h"
#include "Constants.h"

#include <iostream>

Bullet::Bullet(float x, float y, int size): size(size)
{
  isActive = true;

  target.x = x;
  target.y = y;

  position.x = (float) WINDOW_WIDTH;
  position.y = (float) (WINDOW_HEIGHT / 2);

  velocity = target - position;
}

void Bullet::Update(float deltaTime)
{
  position.x = BULLET_SPEED + position.x + velocity.x * deltaTime;
  position.y = BULLET_SPEED + position.y + velocity.y * deltaTime;
  // TODO: if position x or y offscreen, turn off bullet
}

void Bullet::Kill()
{
  isActive = false;
}

bool Bullet::IsActive() const
{
  return isActive;
}
