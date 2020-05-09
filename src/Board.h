#pragma once

#include "Constants.h"
#include "Vec2.h"

#include <iostream>
#include <vector>

struct Brick
{
  Vec2 loc;
  Vec2 vel;
  int size;
  Brick(float x, float y, int size): size(size)
  {
    loc.SetVec(x, y);
    vel.SetVec(0.0f, -10.0f);
  }
};

class Board {
private:
  // TODO: make smart pointers for bricks
  std::vector<Brick> bricks;
public:
  Board();
  ~Board();
  void Update();
  void SpawnBrick(float y);
  void AddBullet(int x, int y);
  bool CheckCollision(int x, int y);
};
