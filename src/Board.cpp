#include "Board.h"

Board::Board(){}

Board::~Board(){}

void Board::Update()
{
  // update position of active bricks based on velocity

  // destroy offscreen bullets

  // destroy deactivet bricks
}

void Board::AddBullet(int x, int y)
{
  // x & y are target!
  // set velocity to go from origin to
  // origin is set at x = WIDTH & y = HEIGHT / 2
}

void Board::SpawnBrick(float y)
{
  Brick brick(0.0f, y, BRICK_SIZE);
  bricks.push_back(brick);
}

bool Board::CheckCollision(int x, int y)
{
  // loop over active brick loc and check for collision


  return false;
}
