#include "Board.h"

#include "../lib/glm/glm.hpp"

#include <iostream>

Board::Board(){}

Board::~Board(){}

void Board::Update(float deltaTime)
{
  for(auto it = bricks.begin(); it != bricks.end(); ++it)
  {
    Brick* b = it->first;
    if (b->IsActive())
    {
      b->Update(deltaTime);
    }
  }

  for(auto it = bullets.begin(); it != bullets.end(); ++it)
  {
    Bullet* b = it->first;
    if (b->IsActive())
    {
      b->Update(deltaTime);
    }
  }
}

void Board::FireBullet(int x, int y)
{
  Bullet* bullet = new Bullet(x, y, BULLET_SIZE);
  bullets[bullet] = bullet;
}

void Board::SpawnBrick(float x, int r, int g, int b)
{
  Brick* brick = new Brick(x, 0.0f, BRICK_SPEED, r, g, b, BRICK_SIZE);
  bricks[brick] = brick;
}

void Board::CheckCollisions()
{
  for(auto it = bricks.begin(); it != bricks.end(); it++)
  {
    Brick* brick = it->first;
    if(brick->IsActive())
    {
      Bullet* deadBullet = nullptr;
      for(auto it2 = bullets.begin(); it2 != bullets.end(); it2++)
      {
        Bullet* bullet = it2->first;
        if(bullet->IsActive())
        {
          // brick - bullet
          if(CollisionBullet(brick, bullet))
          {
            brick->Kill();
            bullet->Kill();
            deadBullet = bullet;
            bricksToKill[brick];
            break;
          }
        }
      }
      // remove dead bullet
      if (deadBullet)
      {
        bullets.erase(deadBullet);
        delete deadBullet;
      }

      // if collide with ground, set static & 0 velocity
      if (brick->position.y >= WINDOW_HEIGHT - BRICK_SIZE)
      {
        brick->SetStatic();
        bricksToAddStatic[brick] = brick;
      }

      // check static brick collision
      for(auto it3 = staticBricks.begin(); it3 != staticBricks.end(); it3++)
      {
        Brick* sb = it3->first;
        if (CollisionBrick(brick, sb))
        {
          brick->SetPosition(Clamp(brick->position.y));
          brick->SetStatic();
          bricksToAddStatic[brick] = brick;
        }
      }
    }
  }

  // remove dead bricks
  for(auto it3 = bricksToKill.begin(); it3 != bricksToKill.end(); it3++)
  {
    Brick* brick = it3->first;
      bricks.erase(brick);
      delete brick;
  }

  // remove static bricks and place in staticBricks
  for(auto it3 = bricksToAddStatic.begin(); it3 != bricksToAddStatic.end(); it3++)
  {
      Brick* brick = it3->first;
      staticBricks[brick] = brick;
      bricks.erase(brick);
  }

  bricksToKill.clear();
  bricksToAddStatic.clear();

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

std::unordered_map<Brick*, Brick*> Board::GetBricks() const
{
  return bricks;
}

std::unordered_map<Brick*, Brick*> Board::GetStaticBricks() const
{
  return staticBricks;
}

std::unordered_map<Bullet*, Bullet*> Board::GetBullets() const
{
  return bullets;
}
