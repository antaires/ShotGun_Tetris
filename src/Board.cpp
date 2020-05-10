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

  // TODO: move static bricks from bricks to staticBricks

  // TODO: destroy offscreen bullets

  // TODO: destroy deactivated bricks
}

void Board::FireBullet(int x, int y)
{
  Bullet* bullet = new Bullet(x, y, BULLET_SIZE);
  bullets.push_back(bullet);
}

void Board::SpawnBrick(float x, int r, int g, int b)
{
  Brick* brick = new Brick(x, 0.0f, BRICK_SPEED, r, g, b, BRICK_SIZE);
  bricks.push_back(brick);
}

void Board::CheckCollision()
{
  // TODO: loop over active brick loc and check for collision, deactivate
  // bullets / bricks hit
  std::vector<int> staticBrickIndex;
  std::vector<int> deadBrickIndex;
  for(int i = 0; i < bricks.size(); ++i) // TODO: switch to for loop, store indices to remove
  {
    Brick* brick = bricks.at(i);
    if(brick->IsActive())
    {
      int deadBullet = -1;
      for(int j = 0; j < bullets.size(); ++j)
      {
        Bullet* bullet = bullets.at(j);
        if(bullet->IsActive())
        {
          // brick - bullet
          if(CollisionBullet(brick, bullet))
          {
            brick->Kill();
            bullet->Kill();
            deadBullet = j;
            deadBrickIndex.push_back(i);
            break;
          }
        }
      }
      // remove bullet
      if (deadBullet >= 0) {bullets.erase(bullets.begin() + deadBullet);}

      // TODO: if collide with ground, set static & 0 velocity
      if (brick->position.y >= WINDOW_HEIGHT - BRICK_SIZE)
      {
        brick->SetStatic();
        staticBrickIndex.push_back(i);
      }

      // static brick collision
      for(auto sb : staticBricks)
      {
        if (CollisionBrick(brick, sb))
        {
          brick->SetStatic();
          staticBrickIndex.push_back(i);
        }
      }

    }
  }

  // remove dead bullets
  for(int i : deadBrickIndex)
  {
    if (bricks.size() > i)
    {
      Brick* brick = bricks.at(i);
      bricks.erase(bricks.begin() + i);
      delete brick;
    }
  }

  // remove static bullets and place in staticBullets
  for(int i : staticBrickIndex)
  {
    if (bricks.size() > i)
    {
      staticBricks.push_back(bricks.at(i));
      bricks.erase(bricks.begin() + i);
    }
  }
  staticBrickIndex.clear();

}

bool Board::CollisionBullet(Brick* brick, Bullet* bullet) const
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


bool Board::CollisionBrick(Brick* b1, Brick* b2) const
{
  if (b1->position.x < b2->position.x + (b2->size - GRACE) &&
      b1->position.x + (b1->size - GRACE) > b2->position.x &&
      b1->position.y < b2->position.y + b2->size &&
      b1->position.y + b1->size > b2->position.y)
      {
        return true;
      }
  return false;
}

std::vector<Brick*> Board::GetBricks() const
{
  return bricks;
}

std::vector<Brick*> Board::GetStaticBricks() const
{
  return staticBricks;
}

std::vector<Bullet*> Board::GetBullets() const
{
  return bullets;
}
