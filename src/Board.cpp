#include "Board.h"

#include "../lib/glm/glm.hpp"

#include <iostream>

Board::Board(){}

Board::~Board(){}

void Board::Update(float deltaTime)
{
  // update position of active bricks based on velocity
  for(auto b : bricks)
  {
    if (b->IsActive())
    {
      b->Update(deltaTime);
    }
  }

  for(auto b : bullets)
  {
    if (b->IsActive())
    {
      b->Update(deltaTime);
    }
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

void Board::CheckCollision()
{
  // TODO: loop over active brick loc and check for collision, deactivate
  // bullets / bricks hit
  for(auto brick : bricks)
  {
    if(brick->IsActive())
    {
      for(auto bullet : bullets)
      {
        if(bullet->IsActive())
        {
          if(Collision(brick, bullet))
          {
            brick->Kill();
            bullet->Kill();
          }
        }
      }
    }
  }
}

bool Board::Collision(Brick* brick, Bullet* bullet) const
{
  if (brick->position.x < bullet->position.x + bullet->size &&
      brick->position.x + brick->size > bullet->position.x &&
      brick->position.y < bullet->position.y + bullet->size &&
      brick->position.y + brick->size > bullet->position.y)
      {
        return true;
      }
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
