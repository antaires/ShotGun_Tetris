#include "Game.h"
#include "Constants.h"

#include <SDL2/SDL.h>

Game::Game(int w, int h) : isRunning(false), width(w), height(h)
{
  // TODO: use smart pointer instead
  board = new Board();
  graphics = new Graphics(width, height);
  ticksLastFrame = 0;
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
  int x, y;
  if (!graphics->ProcessInput(x, y)){isRunning = false;}

  // check collisions

  // update board
  // board->Update();

  // set game state ?
}

void Game::Render() const
{
  graphics->Render(board);
}

bool Game::IsRunning() const
{
  return isRunning;
}
