#pragma once
#include "raylib.h"
#include <cmath>

class Pacman {
  private:
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
    void moveRight();
    void moveLeft();
    void moveUp();
    void moveDown();
};
