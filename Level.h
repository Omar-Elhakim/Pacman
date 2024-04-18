#pragma once

#include "Map.h"
#include "pacman.h"

class Level {
  private:
    Vector2i source, dest;
    int WindowWidth, WindowHeight;
    pacman *Pacman;

  public:
    Map *map = nullptr;
    Level(int WindowWidth, int WindowHeight,Map *map);
    ~Level();
    void StartGame();
};
