#pragma once

#include "Map.h"
#include "pacman.h"
#include "Food.h"
#include "mapmaker.h"
#include "pacman.h"
#include "FileIO.h"
#include "raylib.h"
#include "Ghost.h"

class Level {
  private:
    Vector2 source, dest;
    int WindowWidth, WindowHeight;
    Pacman *pacman;
    Ghost* ghost;
  public:
    Map *map = nullptr;
    Food *food = nullptr;
    Level(int WindowWidth, int WindowHeight,int n);
    ~Level();
    void start();
};
