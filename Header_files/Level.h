#pragma once

#include "Map.h"
#include "pacman.h"
#include "Food.h"
#include "mapmaker.h"
#include "pacman.h"
#include "FileIO.h"
#include "raylib.h"
#include "Ghost.h"
#include "Menu.h"

class Level {
  private:
    Vector2 source, dest;
    int WindowWidth, WindowHeight,n;
    Ghost* ghost;
  public:
      vector<Vector2i> to;
      Pacman* pacman;

      int l;
      bool mapdrawn = false;
      vector<Vector2i> path;
      Vector2 pacmanCenter = { 0 };
      Vector2 ghostCenter = { 0 };
      Vector2 nextcellCenter = { 0 };
      Vector2 relativePos;
      Sound startsound;
      int startc = 0;
    Map *map = nullptr;
    Food *food = nullptr;
    Level(int WindowWidth, int WindowHeight,int n,int l);
    ~Level();
    int ghostsMovement(int i);
    bool start();
};
