#include "Brick.h"
#include "Constants.h"

Brick::Brick(float x, float y, float v, int size): size(size)
{
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
