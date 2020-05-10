#pragma once

#include "Constants.h"
#include "Brick.h"
#include "Bullet.h"


#include <iostream>
#include <vector>

class Board {
private:
  // TODO: make smart pointers
  std::vector<Brick*> bricks;
  std::vector<Brick*> staticBricks;
  std::vector<Bullet*> bullets;
  // TODO: abstract projectile class for both bullet & brick
  bool CollisionBullet(Brick* brick, Bullet* bullet) const;
  bool CollisionBrick(Brick* b1, Brick* b2) const;
public:
  Board();
  ~Board();
  void Update(float deltaTime);
  void SpawnBrick(float y, int r, int g, int b);
  void FireBullet(int x, int y);
  void CheckCollision();
  std::vector<Brick*> GetBricks() const;
  std::vector<Bullet*> GetBullets() const;
  std::vector<Brick*> GetStaticBricks() const;
};
