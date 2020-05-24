#pragma once

#include "Constants.h"
#include "Brick.h"
#include "Bullet.h"
#include "Shape.h"
#include "Random.h"

#include <iostream>
#include <vector>
#include <unordered_map>

class Board {
private:
  float lastShapeSpawnPosition;
  // TODO: make smart pointers
  std::unordered_map<Shape*, Shape*> shapes;
  std::unordered_map<Brick*, Brick*> staticBricks;
  std::unordered_map<Bullet*, Bullet*> bullets;

  std::unordered_map<Brick*, Brick*> bricksToAddStatic;
  //std::unordered_map<Brick*, Brick*> bricksToKill;
  std::unordered_map<Shape*, Shape*> emptyShapes;
  std::unordered_map<Bullet*, Bullet*> bulletsToRemove;

  // TODO: abstract projectile class for both bullet & brick
  bool CollisionShape(Shape* shape, Bullet* bullet) const;
  bool CollisionShapeBrick(Shape* shape, Brick* brick) const;
  bool CollisionBullet(Brick* brick, Bullet* bullet) const;
  bool CollisionBrick(Brick* b1, Brick* b2) const;
  //void RemoveDeadBricks();
  void RemoveDeadBullets();
  void UpdateStaticBricks();
  void RemoveEmptyShapes();
  std::vector<Brick*> SortBricksByDistance(std::unordered_map<Brick*, Brick*> bricks, Bullet* bullet);
public:
  Board();
  ~Board();
  void Update(float deltaTime);
  Shape* SpawnShape(Random* random);
  void FireBullet(int x, int y);
  void CheckCollisions();
  bool CheckRows();

  std::unordered_map<Shape*, Shape*> GetShapes() const;
  std::unordered_map<Bullet*, Bullet*> GetBullets() const;
  std::unordered_map<Brick*, Brick*> GetStaticBricks() const;
};
