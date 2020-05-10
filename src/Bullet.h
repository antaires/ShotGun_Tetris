#pragma once

#include "../lib/glm/glm.hpp"


class Bullet
{
private:
public:
  glm::vec2 target;
  glm::vec2 position;
  glm::vec2 velocity;
  int size;

  Bullet(float x, float y, int size);
  void Update(float deltaTime);
};
