#pragma once

#include <random>
#include <time.h>

class Random
{
private:
  static Random *instance;
  Random()
  {
    srand(time(NULL));
  }

public:
  static Random *GetInstance()
  {
    if (!instance){instance = new Random();}
    return instance;
  }

  float GetRand(int min, int max)
  {
    return rand() % (max - min + 1) + min;
  }
};

Random *Random::instance = 0;
