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
  std::vector<Bullet*> bullets;
public:
  Board();
  ~Board();
  void Update(float deltaTime);
  void SpawnBrick(float y);
  void FireBullet(int x, int y);
  bool CheckCollision(int x, int y);
  std::vector<Brick*> GetBricks() const;
  std::vector<Bullet*> GetBullets() const;
};
