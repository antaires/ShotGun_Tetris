#pragma once

#include "Constants.h"
#include "Brick.h"


#include <iostream>
#include <vector>

class Board {
private:
  // TODO: make smart pointers for bricks
  std::vector<Brick*> bricks;
public:
  Board();
  ~Board();
  void Update(float deltaTime);
  void SpawnBrick(float y);
  void AddBullet(int x, int y);
  bool CheckCollision(int x, int y);
  std::vector<Brick*> GetBricks() const;
};
