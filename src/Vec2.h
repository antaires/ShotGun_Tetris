#pragma once

class Vec2
{
private:
  float x;
  float y;
public:
  void SetVec(float x_, float y_) { x = x_; y = y_;}
  void Add(Vec2& a) { x+=a.x; y+=a.y;}
  void Sub(Vec2& a) { x-=a.x; y-=a.y;}
};
