#pragma once

#include "Brick.h"
#include "Random.h"

#include "../lib/glm/glm.hpp"
#include <unordered_map>

enum Shapes { Single = 0, Bar = 1, Square = 2, Hook = 3, Zag = 4};

class Shape
{
private:
  Brick* mainBrick;
  std::unordered_map<Brick*, Brick*> bricks;
  Brick* SpawnBrick(float x, float y, int r, int g, int b);
  void SpawnSingle(float brickX, int red, int green, int blue);
  void SpawnBar(float centerBrickX, int red, int green, int blue, bool rotate);
  void SpawnSquare(float xOrigin, int red, int green, int blue);
public:
  glm::vec2 position;
  glm::vec2 velocity;
  int height;
  int width;
  Shape(Random* random);
  std::unordered_map<Brick*, Brick*> GetBricks();
  void RemoveBrick(Brick* brick);
  bool IsEmpty();
  void Update(float deltaTime);
};
