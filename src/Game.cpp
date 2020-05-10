#include "Game.h"
#include "Constants.h"

#include <iostream>

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
  // TODO: causing seg fault
  //delete graphics;
  //delete board;
}

void Game::Start()
{
  isRunning = true;

  // generate bricks TODO: make randomly generated at top of screen
  float brickX = (float) width / 2;

  // update board
  board->SpawnBrick(brickX);
}

void Game::Update()
{
  // wait until FRAME_TARGET_TIME reached since last frame
  while(!SDL_TICKS_PASSED(SDL_GetTicks(), ticksLastFrame + FRAME_TARGET_TIME));
  float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;
  deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;
  ticksLastFrame = SDL_GetTicks();

  // use delta time to update my game objects

  // process ProcessInput
  int x = -1, y = -1;
  if (!graphics->ProcessInput(x, y)){isRunning = false;}
  if (x > 0 && y > 0)
  {
    // fire bullet
    board->FireBullet(x, y);
    std::cout<<"\nFire bullet: "<< x << " " << y;
  }

  // check collisions
  board->CheckCollision(); // if collision, mark to explode brick!

  // generate bricks TODO: make randomly generated at top of screen
  //float brickX = (float) width / 2;

  // update board
  //board->SpawnBrick(brickX);
  board->Update(deltaTime);

  // set game state
}


void Game::Render() const
{
  graphics->Render(board);
}

bool Game::IsRunning() const
{
  return isRunning;
}
