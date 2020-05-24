#include "Shape.h"
#include "Constants.h"
#include <cmath>

Shape::Shape(Random* random, float prevPos)
{

  // create bricks according to type -- memory for bricks
  // is requested here, but not destroyed when the shape is - rather
  // a brick is only destroyed once its 'row line' is erased

  // prevent shapes spawning over other shapes
  float xOrigin = prevPos;
  while (std::abs(xOrigin - prevPos) < BRICK_SIZE * 5)
  {
    xOrigin = random->GetRand(0, WINDOW_WIDTH - BRICK_SIZE);
  }

  int red   = (int) random->GetRand(0, 255);
  int green = (int) random->GetRand(0, 255);
  int blue  = (int) random->GetRand(0, 255);

  int shapeIndex = (int) random->GetRand(0, 5);
  bool rotate    = (int) random->GetRand(0, 1);
  bool mirror    = (int) random->GetRand(0, 1);

  switch(shapeIndex)
  {
    case Shapes::Single:
      SpawnSingle(xOrigin, red, green, blue);
      break;
    case Shapes::Bar:
      SpawnBar(xOrigin, red, green, blue, rotate);
      break;
    case Shapes::Square:
      SpawnSquare(xOrigin, red, green, blue);
      break;
    default:
      SpawnSingle(xOrigin, red, green, blue);
      break;
  }
}

Brick* Shape::SpawnBrick(float x, float y, int r, int g, int b)
{
  Brick* brick = new Brick(x, y, BRICK_SPEED, r, g, b, BRICK_SIZE);
  bricks[brick] = brick;
  return brick;
}

void Shape::SpawnSingle(float xOrigin, int red, int green, int blue)
{
  mainBrick = SpawnBrick((float) Clamp((int)xOrigin), 0, red, green, blue);

  position.x = xOrigin;
  position.y = 0;
  velocity.x = mainBrick->velocity.x;
  velocity.y = mainBrick->velocity.y;
  height = BRICK_SIZE;
  width = BRICK_SIZE;
}

void Shape::SpawnBar(float xOrigin, int red, int green, int blue, bool rotate)
{
  // VERTICAL
  if (rotate)
  {
    mainBrick = SpawnBrick((float) Clamp((int)xOrigin), 0, red, green, blue);
    for(int i = 1; i < 4; ++i)
    {
      SpawnBrick((float) Clamp((int)xOrigin), BRICK_SIZE * i, red, green, blue);
    }
    position.x = xOrigin;
    position.y = 0;
    height = BRICK_SIZE;
    width = BRICK_SIZE * 4;
    velocity.x = mainBrick->velocity.x;
    velocity.y = mainBrick->velocity.y;
  }

  // HORIZONTAL
  else
  {
    mainBrick = SpawnBrick((float) Clamp((int)xOrigin), 0, red, green, blue);
    for(int i = 0; i < 3; ++i)
    {
      SpawnBrick((float) Clamp((int)xOrigin + BRICK_SIZE * i), 0, red, green, blue);
    }
    position.x = xOrigin;
    position.y = 0;
    height = BRICK_SIZE * 4;
    width = BRICK_SIZE;
    velocity.x = mainBrick->velocity.x;
    velocity.y = mainBrick->velocity.y;
  }
}

void Shape::SpawnSquare(float xOrigin, int red, int green, int blue)
{
  mainBrick = SpawnBrick((float) Clamp((int)xOrigin), 0, red, green, blue);
  SpawnBrick((float) Clamp((int)xOrigin + BRICK_SIZE), 0, red, green, blue);
  SpawnBrick((float) Clamp((int)xOrigin), BRICK_SIZE, red, green, blue);
  SpawnBrick((float) Clamp((int)xOrigin + BRICK_SIZE), BRICK_SIZE, red, green, blue);

  position.x = xOrigin;
  position.y = 0;
  velocity.x = mainBrick->velocity.x;
  velocity.y = mainBrick->velocity.y;
  height = BRICK_SIZE * 2;
  width = BRICK_SIZE * 2;
}

std::unordered_map<Brick*, Brick*> Shape::GetBricks()
{
  return bricks;
}

void Shape::RemoveBrick(Brick* brick)
{
  bricks.erase(brick);
}

bool Shape::IsEmpty()
{
  return bricks.empty();
}

void Shape::Update(float deltaTime)
{
  for(auto it = bricks.begin(); it != bricks.end(); it++)
  {
    Brick* b = it->first;
    if (b->IsActive())
    {
      b->Update(deltaTime);
    }
  }

  // update shape bounding box
  // todo - remove repetition between this & brick update
  // todo - add active check
  float tempX = position.x + velocity.x * deltaTime;
  float tempY = position.y + velocity.y * deltaTime;

  // todo this will become inaccurate if bricks removed
  if (tempY >= WINDOW_HEIGHT + height)
  {
    tempY = WINDOW_HEIGHT + height;
  }

  position.x = tempX;
  position.y = tempY;
}
