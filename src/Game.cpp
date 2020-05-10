#include "Game.h"
#include "Constants.h"

#include <iostream>
#include <random>
#include <time.h>
#include <string>

#include <SDL2/SDL.h>

Game::Game(int w, int h) : isRunning(false), width(w), height(h)
{
  srand(time(NULL));
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

  float brickX = Random(0, WINDOW_WIDTH - BRICK_SIZE);
  board->SpawnBrick((float) Clamp((int)brickX));

  // process ProcessInput
  int x = -1, y = -1;
  if (!graphics->ProcessInput(x, y)){isRunning = false;}
  if (x > 0 && y > 0)
  {
    board->FireBullet(x, y);
  }

  board->CheckCollision();

  board->Update(deltaTime);

  // set game state
}

float Game::Random(int min, int max)
{
  return rand() % (max - min + 1) + min;
}

int Game::Clamp(int num)
{
  // keep pos mult of 10 for even bricks
  if (num == 0){return (int) num;}
  if (num % 10 != 0)
  {
    std::string strNum = std::to_string(num);
    int leastDigit = strNum.at(strNum.size()-1);
    if (leastDigit >= 5)
    {
        return num + 10 - leastDigit;
    } else
    {
        return num - leastDigit;
    }
  }
  return num;
}

void Game::Render() const
{
  graphics->Render(board);
}

bool Game::IsRunning() const
{
  return isRunning;
}
