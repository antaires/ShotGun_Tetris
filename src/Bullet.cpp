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

  velocity = glm::normalize(target-position);
}

void Bullet::Update(float deltaTime)
{
  position.x = (position.x + (velocity.x * BULLET_SPEED) * deltaTime);
  position.y = (position.y + (velocity.y * BULLET_SPEED) * deltaTime);
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
