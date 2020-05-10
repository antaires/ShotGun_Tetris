#pragma once

#include "Graphics.h"

class Game {
  private:
    bool isRunning;
    Graphics* graphics;
    Board* board;
    int width;
    int height;
    float ticksLastFrame;
    float Random(int min, int max);
    int Clamp(int num);
  public:
    Game(int w, int h);
    ~Game();
    void Start();
    void Update();
    void Render() const;
    bool IsRunning() const;
};
