#include "Board.h"

#include <iostream>

Board::Board(){}

Board::~Board(){}

void Board::Update(float deltaTime)
{
  // TODO: use deltaTime
  // update position of active bricks based on velocity
  for(auto b : bricks)
  {
    b->Update(deltaTime);
  }

  // destroy offscreen bullets

  // destroy deactivet bricks
}

void Board::AddBullet(int x, int y)
{
  // x & y are target!
  // set velocity to go from origin to
  // origin is set at x = WIDTH & y = HEIGHT / 2
}

void Board::SpawnBrick(float x)
{
  Brick* brick = new Brick(x, 0.0f, BRICK_SIZE);
  bricks.push_back(brick);
}

bool Board::CheckCollision(int x, int y)
{
  // loop over active brick loc and check for collision

  return false;
}

std::vector<Brick*> Board::GetBricks() const
{
  return bricks;
}
