#pragma once

#include "Map.h"
#include "pacman.h"

class Level {
  private:
    Vector2i source, dest;
    int WindowWidth, WindowHeight;
    pacman tebry;

  public:
    Map *map = nullptr;
    Level(int WindowWidth, int WindowHeight);
    ~Level();
    void notgame();
};
