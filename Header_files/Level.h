#pragma once

#include "Map.h"
#include "pacman.h"
#include "Food.h"
#include "mapmaker.h"
#include "pacman.h"
#include "FileIO.h"
#include "raylib.h"

class Level {
  private:
    Vector2i source, dest;
    int WindowWidth, WindowHeight;
    Pacman *pacman;

  public:
    Map *map = nullptr;
    Food *food = nullptr;
    Level(int WindowWidth, int WindowHeight,int n);
    ~Level();
    void start();
};
