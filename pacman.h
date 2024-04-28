#pragma once
#include "Map.h"
#include "raylib.h"

class Pacman {
  private:
    Image PacmanImage;
    Texture2D pacmanText;
    Rectangle AnimationBox;
    Vector2 ImageSize;
    int x;
    float speed;
    int a;
    Map *map;

  public:
      Vector2 InitialPosition;

    Vector2 direction;
    Pacman(Map *map);
    ~Pacman();
    void draw();
    void move();
    void goRight();
    void goLeft();
    void goUp();
    void goDown();
    void update();
};
