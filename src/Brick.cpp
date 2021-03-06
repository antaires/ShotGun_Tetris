#include "Brick.h"
#include "Constants.h"

Brick::Brick(float x, float y, float v, int r, int g, int b, int size): size(size)
{
  red   = r;
  green = g;
  blue  = b;

  isActive = true;
  isStatic = false;

  position.x = x;
  position.y = y;

  velocity.x =  0;
  velocity.y = v;
}

void Brick::Update(float deltaTime)
{
  float tempX = position.x + velocity.x * deltaTime;
  float tempY = position.y + velocity.y * deltaTime;

  if (tempY >= WINDOW_HEIGHT + BRICK_SIZE)
  {
    tempY = WINDOW_HEIGHT + BRICK_SIZE;
  }

  position.x = tempX;
  position.y = tempY;
}

void Brick::Kill()
{
  // TODO: flashing colors / explosion here
  isActive = false;
}

bool Brick::IsActive() const
{
  return isActive;
}

void Brick::SetStatic()
{
  velocity.x = 0;
  velocity.y = 0;
  isStatic = true;
  // todo move this here? SetPosition(Clamp(brick->position.y));
}

bool Brick::IsStatic() const
{
  return isStatic;
}

void Brick::SetPosition(int y)
{
  position.y = y;
}
