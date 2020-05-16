#include "Shape.h"
#include "Constants.h"

Shape::Shape(Random* random)
{
  // create bricks according to type -- memory for bricks
  // is requested here, but not destroyed when the shape is - rather
  // a brick is only destroyed once its 'row line' is erased
  float xOrigin = random->GetRand(0, WINDOW_WIDTH - BRICK_SIZE);

  int red   = (int) random->GetRand(0, 255);
  int green = (int) random->GetRand(0, 255);
  int blue  = (int) random->GetRand(0, 255);

  int shapeIndex = (int) random->GetRand(0, 5);

  // todo update for other SHAPES
  position.x = xOrigin;
  position.y = 0;
  height = BRICK_SIZE;
  width = BRICK_SIZE;

  SpawnBrick((float) Clamp((int)xOrigin), 0, red, green, blue);

  /*
  // todo : set position and height / width depending on shape
  switch(shapeIndex)
  {
    case Shapes::Single:
      //SpawnSingle(xOrigin, red, green, blue);
      SpawnBrick((float) Clamp((int)xOrigin), 0, red, green, blue);
      break;
    case Shapes::Bar:
      //SpawnBar(xOrigin, red, green, blue);
      SpawnBrick((float) Clamp((int)xOrigin), 0, red, green, blue);
    default:
      //SpawnSingle(xOrigin, red, green, blue);
      SpawnBrick((float) Clamp((int)xOrigin), 0, red, green, blue);
      break;
  } */
}

void Shape::SpawnBrick(float x, float y, int r, int g, int b)
{
  Brick* brick = new Brick(x, y, BRICK_SPEED, r, g, b, BRICK_SIZE);
  bricks[brick] = brick;
}

void Shape::SpawnSingle(float brickX, int red, int green, int blue)
{
  // board->SpawnBrick((float) Clamp((int)brickX), 0, red, green, blue);
}

void Shape::SpawnBar(float x_, int red, int green, int blue)
{
  /*
  float x = (float) Clamp((int)x);
  std::vector<Brick*> shape;
  Random *random = random->GetInstance();
  if ( random->GetRand(1, 10) < 5 )
  {
    for(int i = 0; i < 4; ++i)
    {
      shape.push_back(board->SpawnBrick(x, BRICK_SIZE * i, red, green, blue));
    }
    for(auto b: shape)
    {
      for(auto p: shape)
      {
        b->SetFriend(p);
        p->SetFriend(b);
      }
    }
  }
  else
  {
    if (x - (BRICK_SIZE * 5) < 0)
    {
      for(int i = 0; i < 4; ++i)
      {
        shape.push_back(board->SpawnBrick(x + BRICK_SIZE * i, 0, red, green, blue));
      }
      for(auto b: shape)
      {
        for(auto p: shape)
        {
          b->SetFriend(p);
          p->SetFriend(b);
        }
      }
    }
    else
    {
      for(int i = 0; i < 4; ++i)
      {
        shape.push_back(board->SpawnBrick(x - BRICK_SIZE * i, 0, red, green, blue));
      }
      for(auto b: shape)
      {
        for(auto p: shape)
        {
          b->SetFriend(p);
          p->SetFriend(b);
        }
      }
    }
  }
  */
}

std::unordered_map<Brick*, Brick*> Shape::GetBricks()
{
  return bricks;
}

void Shape::RemoveBrick(Brick* brick)
{
  bricks.erase(brick);
}

bool Shape::IsEmpty()
{
  return bricks.empty();
}

void Shape::Update(float deltaTime)
{
  for(auto it = bricks.begin(); it != bricks.end(); it++)
  {
    Brick* b = it->first;
    //if (b->IsActive())
    //{
    b->Update(deltaTime);
    //}
  }
}
