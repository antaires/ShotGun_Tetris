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

  position.x = tempX;
  position.y = tempY; //tempY > WINDOW_HEIGHT ? WINDOW_HEIGHT : (float) tempY;
}

void Brick::Kill()
{
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
}

bool Brick::IsStatic() const
{
  return isStatic;
}
