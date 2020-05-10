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
  bool Collision(Brick* brick, Bullet* bullet) const;
public:
  Board();
  ~Board();
  void Update(float deltaTime);
  void SpawnBrick(float y);
  void FireBullet(int x, int y);
  void CheckCollision();
  std::vector<Brick*> GetBricks() const;
  std::vector<Bullet*> GetBullets() const;
};
