#pragma once

#include "../lib/glm/glm.hpp"
#include <unordered_map>

class Brick
{
private:
public:
  glm::vec2 position;
  glm::vec2 velocity;
  std::unordered_map<Brick*, Brick*> friends;
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
  void SetPosition(int y);
  void SetFriend(Brick* brick);
  std::unordered_map<Brick*, Brick*> GetFriends(); // can't be const because if shot, must delete
};
