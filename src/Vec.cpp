#include "Vec2.h"

Vec2::Vec2(){}

Vec2::Vec2(float x_, float y_)
{
  x = x_;
  y = y_;
}

void Vec2::SetVec(float x_, float y_)
{
  x = x_;
  y = y_;
}

Vec2 Vec2::operator + (Vec2& a)
{
  Vec2 v;
  v.SetVec(x+a.x, y+a.y);
  return v;
}

Vec2 Vec2::operator - (Vec2& a)
{
  Vec2 v;
  v.SetVec(x-a.x, y-a.y);
  return v;
}
