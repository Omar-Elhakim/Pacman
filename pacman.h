#pragma once
#include "raylib.h"
#include <cmath>

class Pacman {
  public:
    Image PacmanImage;
    Texture2D pacmanText;
    Rectangle AnimationBox;
    Vector2 InitialPosition;
    Vector2 direction;
    float x;
    float speed;
    int a;

  public:
    Pacman();
    ~Pacman();
    void draw();
    void move();
    void goRight();
    void goLeft();
    void goUp();
    void goDown();
};
