#pragma once

#include "Constants.h"
#include "Brick.h"
#include "Bullet.h"


#include <iostream>
#include <vector>
#include <unordered_map>

class Board {
private:
  // TODO: make smart pointers
  std::unordered_map<Brick*, Brick*> bricks;
  std::unordered_map<Brick*, Brick*> staticBricks;
  std::unordered_map<Bullet*, Bullet*> bullets;

  std::unordered_map<Brick*, Brick*> bricksToAddStatic;
  std::unordered_map<Brick*, Brick*> bricksToKill;

  // TODO: abstract projectile class for both bullet & brick
  bool CollisionBullet(Brick* brick, Bullet* bullet) const;
  bool CollisionBrick(Brick* b1, Brick* b2) const;
public:
  Board();
  ~Board();
  void Update(float deltaTime);
  void SpawnBrick(float y, int r, int g, int b);
  void FireBullet(int x, int y);
  void CheckCollisions();
  bool CheckRows();
  std::unordered_map<Brick*, Brick*> GetBricks() const;
  std::unordered_map<Bullet*, Bullet*> GetBullets() const;
  std::unordered_map<Brick*, Brick*> GetStaticBricks() const;
};
