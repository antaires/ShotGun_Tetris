#include "Board.h"

#include "../lib/glm/glm.hpp"

#include <iostream>

Board::Board(){}

Board::~Board(){}

void Board::Update(float deltaTime)
{
  for(auto it = shapes.begin(); it != shapes.end(); ++it)
  {
    Shape* shape = it->first;
    shape->Update(deltaTime);
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

Shape* Board::SpawnShape(Random* random)
{
  // add shape to list of active SHAPES
  Shape* shape = new Shape(random);
  shapes[shape] = shape;
  return shape;
}

void Board::CheckCollisions()
{

  for(auto itShapes = shapes.begin(); itShapes != shapes.end(); itShapes++)
  {
    Shape* shape = itShapes->first;

    // COLLISION SHAPE - BULLET
    Bullet* deadBullet = nullptr;
    for(auto itBullets = bullets.begin(); itBullets != bullets.end(); itBullets++)
    {
      Bullet* bullet = itBullets->first;
      if(bullet->IsActive()) // todo need to check this? I remove dead bullets
      {
        if(CollisionShape(shape, bullet))
        {
          // todo - it seems that the shape bounding box if off?
          auto bricks = shape->GetBricks();
          for(auto itBricks = bricks.begin(); itBricks != bricks.end(); itBricks++)
          {
            Brick* brick = itBricks->first;
            if (CollisionBullet(brick, bullet))
            {
              shape->RemoveBrick(brick);
              brick->Kill();
              bullet->Kill();
              deadBullet = bullet;
              // todo -> free memory for brick here?
              //bricksToKill[brick];
              // break;
            }
          }
        }
      }
      else
      {
        bulletsToRemove[bullet] = bullet;
      }
    }
    // remove dead bullet for next shape
    if (deadBullet)
    {
      bullets.erase(deadBullet);
      delete deadBullet;
    }
    // remove offscreen bullets
    RemoveDeadBullets();

    // COLLISION SHAPE - GROUND
    if (shape->position.y >= WINDOW_HEIGHT - shape->height)
    {
      auto bricks = shape->GetBricks();
      for (auto itBricks = bricks.begin(); itBricks != bricks.end(); itBricks++)
      {
        Brick* b = itBricks->first;
        shape->RemoveBrick(b);
        b->SetStatic();
        b->SetPosition(Clamp(b->position.y));
        bricksToAddStatic[b] = b;
      }
      // todo skip to next shape at this point?
    }

    // COLLISION SHAPE - STATIC BRICKS
    for(auto itStatic = staticBricks.begin(); itStatic != staticBricks.end(); itStatic++)
    {
      Brick* sb = itStatic->first;
      if (CollisionShapeBrick(shape, sb))
      {
        bool hasCollision = false;
        auto bricks = shape->GetBricks();
        for(auto itBricks = bricks.begin(); itBricks != bricks.end(); itBricks++)
        {
          Brick* brick = itBricks->first;
          if (CollisionBrick(brick, sb))
          {
            hasCollision = true;
            break;
          }
        }
        if (hasCollision)
        {
          for(auto itBricks = bricks.begin(); itBricks != bricks.end(); itBricks++)
          {
            Brick* brick = itBricks->first;
            shape->RemoveBrick(brick);
            brick->SetPosition(Clamp(brick->position.y));
            brick->SetStatic();
            bricksToAddStatic[brick] = brick;
          }
        }
      }
    }

    if (shape->IsEmpty())
    {
      emptyShapes[shape] = shape;
    }
  }

  //RemoveDeadBricks();
  UpdateStaticBricks();
  RemoveEmptyShapes();
}

bool Board::CollisionShape(Shape* shape, Bullet* bullet) const
{
  if (shape->position.x < bullet->position.x + bullet->size &&
      shape->position.x + shape->width > bullet->position.x &&
      shape->position.y < bullet->position.y + bullet->size &&
      shape->position.y + shape->height > bullet->position.y)
      {
        return true;
      }
  return false;
}

bool Board::CollisionShapeBrick(Shape* shape, Brick* brick) const
{
  if (shape->position.x < brick->position.x + brick->size &&
      shape->position.x + shape->width > brick->position.x &&
      shape->position.y < brick->position.y + brick->size &&
      shape->position.y + shape->height > brick->position.y)
      {
        return true;
      }
  return false;
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

/* TODO needed? replaced with shapes ...
void Board::RemoveDeadBricks()
{
  for(auto it3 = bricksToKill.begin(); it3 != bricksToKill.end(); it3++)
  {
    Brick* brick = it3->first;
      bricks.erase(brick);
      delete brick;
  }
  bricksToKill.clear();
}*/

void Board::UpdateStaticBricks()
{
  for(auto it3 = bricksToAddStatic.begin(); it3 != bricksToAddStatic.end(); it3++)
  {
      Brick* brick = it3->first;
      staticBricks[brick] = brick;
      // bricks.erase(brick);
  }
  bricksToAddStatic.clear();
}

void Board::RemoveEmptyShapes()
{
  for(auto it = emptyShapes.begin(); it != emptyShapes.end(); it++)
  {
    Shape* shape = it->first;
    shapes.erase(shape);
  }
  emptyShapes.clear();
}

void Board::RemoveDeadBullets()
{
  for(auto it = bulletsToRemove.begin(); it != bulletsToRemove.end(); it++)
  {
    Bullet* bullet = it->first;
    bullets.erase(bullet);
    // todo delete bullet here
  }
  bulletsToRemove.clear();
}

bool Board::CheckRows()
{
  // TODO: check ALL rows, store in 2d map sorted by row
  // if 1 row full, remove it and lower ALL bricks ABOVE it

  // sort static bricks by y and filter out those not on bottom
  std::unordered_map<int, Brick*> bottomRow;
  for(auto it = staticBricks.begin(); it != staticBricks.end(); ++it)
  {
    Brick* b = it->first;
    if (b->position.y == WINDOW_HEIGHT - BRICK_SIZE)
    {
      int index = Clamp(b->position.x);
      bottomRow[index] = b;
    }
  }

  if (bottomRow.size() == WINDOW_WIDTH / BRICK_SIZE)
  {
    // TODO: flash bricks
    // delete all bricks
    for(auto it = bottomRow.begin(); it != bottomRow.end(); ++it)
    {
      Brick* b = it->second;
      staticBricks.erase(b);
      delete b;
    }
    // drop all static down 1 brick space
    for(auto it = staticBricks.begin(); it != staticBricks.end(); ++it)
    {
      Brick* b = it->first;
      b->SetPosition(Clamp(b->position.y + BRICK_SIZE));
    }
    return true;
  }

  return false;
}

std::unordered_map<Shape*, Shape*>  Board::GetShapes() const
{
  // TODO - alternately, could loop over shapes and make list of bricks?
  return shapes;
}

std::unordered_map<Brick*, Brick*> Board::GetStaticBricks() const
{
  return staticBricks;
}

std::unordered_map<Bullet*, Bullet*> Board::GetBullets() const
{
  return bullets;
}
