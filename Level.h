#pragma once

#include "Map.h"
#include "pacman.h"

class Level {
  private:
    Vector2i source, dest;
    int WindowWidth, WindowHeight;
    Pacman *pacman;

  public:
    Map *map = nullptr;
    Level(int WindowWidth, int WindowHeight);
    ~Level();
    void start();
};
