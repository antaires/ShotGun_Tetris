#include "Game.h"
#include "Constants.h"
#include "Random.h"

#include <iostream>
#include <string>

#include <SDL2/SDL.h>

Game::Game(int w, int h) : isRunning(false), width(w), height(h)
{
  // TODO: use smart pointer instead
  board = new Board();
  graphics = new Graphics(width, height);
  ticksLastFrame;
}

Game::~Game()
{
  // TODO: delete all bullets/ bricks
  //delete graphics;
  //delete board;
}

void Game::Start()
{
  isRunning = true;
}

void Game::Update()
{
  // wait until FRAME_TARGET_TIME reached since last frame
  while(!SDL_TICKS_PASSED(SDL_GetTicks(), ticksLastFrame + FRAME_TARGET_TIME));
  float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;
  deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;
  ticksLastFrame = SDL_GetTicks();

  Random *random = random->GetInstance();
  if ( random->GetRand(0, 11) < 3 )
  {
    float brickX = random->GetRand(0, WINDOW_WIDTH - BRICK_SIZE);

    int red   = (int) random->GetRand(0, 255);
    int green = (int) random->GetRand(0, 255);
    int blue  = (int) random->GetRand(0, 255);

    board->SpawnBrick((float) Clamp((int)brickX), red, green, blue);
  }

  // process ProcessInput
  int x = -1, y = -1;
  if (!graphics->ProcessInput(x, y)){isRunning = false;}
  if (x > 0 && y > 0)
  {
    board->FireBullet(x, y);
  }

  board->CheckCollisions();


  board->Update(deltaTime);

  // set game state
}

int Game::Clamp(int num)
{
  // get closet mult of BRICK_SIZE
  if (num == 0){return num;}
  int remainder = num % BRICK_SIZE;
  if (remainder == 0){return num;}
  if (remainder >= BRICK_SIZE / 2)
  { // round up
      return num + BRICK_SIZE - remainder;
  } // round down
  return num - remainder;
}

void Game::Render() const
{
  graphics->Render(board);
}

bool Game::IsRunning() const
{
  return isRunning;
}
