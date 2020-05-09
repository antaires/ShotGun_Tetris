#pragma once

class Vec2
{
private:
public:
  float x;
  float y;

  Vec2();
  
  Vec2(float x, float y);

  void SetVec(float x_, float y_);

  Vec2 operator + (Vec2& a);

  Vec2 operator - (Vec2& a);

};
