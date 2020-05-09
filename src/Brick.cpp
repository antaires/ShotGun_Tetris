#include "Brick.h"
#include "Constants.h"

#include <iostream>

Brick::Brick(float x, float y, int size): size(size)
{
  position.x = x; // == 1/2 width
  position.y = y; // == 0

  velocity.x =  -15; // should be 0!
  velocity.y = 0; //  should be 15
}

void Brick::Update(float deltaTime)
{
  int tempX = position.x + velocity.x * deltaTime;
  int tempY = position.y + velocity.y * deltaTime;

  position.x = (float) tempX;
  position.y = (float) tempY; //tempY > WINDOW_HEIGHT ? WINDOW_HEIGHT : (float) tempY;

  std::cout<<"\n position X" << position.x <<" Y"<< position.y;
}
