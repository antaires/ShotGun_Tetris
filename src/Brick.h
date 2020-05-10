#pragma once

#include "../lib/glm/glm.hpp"


class Brick
{
private:
public:
  glm::vec2 position;
  glm::vec2 velocity;
  int size;
  bool isActive;

  Brick(float x, float y, float v, int size);
  void Update(float deltaTime);
  void Kill();
  bool IsActive() const;
};
