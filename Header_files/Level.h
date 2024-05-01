#pragma once

#include "Map.h"
#include "pacman.h"
#include "Food.h"

class Level {
  private:
    Vector2i source, dest;
    int WindowWidth, WindowHeight;
    Pacman *pacman;

  public:
    Map *map = nullptr;
    Food *food = nullptr;
    Level(int WindowWidth, int WindowHeight);
    ~Level();
    void start();
};
