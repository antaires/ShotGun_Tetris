#include "Board.h"

#include <iostream>

Board::Board(){}

Board::~Board(){}

void Board::Update(float deltaTime)
{
  // update position of active bricks based on velocity
  for(auto b : bricks)
  {
    b->Update(deltaTime);
  }

  for(auto b : bullets)
  {
    b->Update(deltaTime);
  }

  // TODO: destroy offscreen bullets

  // TODO: destroy deactivated bricks
}

void Board::FireBullet(int x, int y)
{
  Bullet* bullet = new Bullet(x, y, BULLET_SIZE);
  bullets.push_back(bullet);
}

void Board::SpawnBrick(float x)
{
  Brick* brick = new Brick(x, 0.0f, 15.0f, BRICK_SIZE);
  bricks.push_back(brick);
}

bool Board::CheckCollision(int x, int y)
{
  // TODO: loop over active brick loc and check for collision
  return false;
}

std::vector<Brick*> Board::GetBricks() const
{
  return bricks;
}

std::vector<Bullet*> Board::GetBullets() const
{
  return bullets;
}
