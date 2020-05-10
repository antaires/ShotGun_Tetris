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
  bool isStatic;
  int red;
  int green;
  int blue;

  Brick(float x, float y, float v, int r, int g, int b, int size);
  void Update(float deltaTime);
  void Kill();
  bool IsActive() const;
  void SetStatic();
  bool IsStatic() const;
};
