#include "Brick.h"
#include "Constants.h"

#include <iostream>

Brick::Brick(float x, float y, int size): size(size)
{
  position.x = x; // == 1/2 width
  position.y = y; // == 0

  velocity.x =  0; // should be 0!
  velocity.y = 15; //  should be 15
}

void Brick::Update(float deltaTime)
{
  float tempX = position.x + velocity.x * deltaTime;
  float tempY = position.y + velocity.y * deltaTime;

  position.x = tempX;
  position.y = tempY; //tempY > WINDOW_HEIGHT ? WINDOW_HEIGHT : (float) tempY;

  std::cout<<"\n position X" << position.x <<" Y"<< position.y;
}
