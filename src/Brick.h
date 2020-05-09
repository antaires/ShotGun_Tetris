#pragma once

#include "../lib/glm/glm.hpp"


class Brick
{
private:
public:
  glm::vec2 position;
  glm::vec2 velocity;
  int size;

  Brick(float x, float y, int size);
  void Update(float deltaTime);
};
