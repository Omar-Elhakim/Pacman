#pragma once
#include "raylib.h"
#include <cmath>

class pacman {
  public:
    pacman();
    ~pacman();
    Image pac;
    Texture2D pacman1;
    Rectangle box;
    Vector2 position;
    Vector2 direction;
    float speed;
    float x;
    int a;
    void f();
    void draw();
    // void funco(Texture2D pacman1, Vector2 position, Vector2 direction, Rectangle box, Image pac, float speed, float
    // x, int a);
    void moveRight();
    void moveLeft();
    void moveUp();
    void moveDown();
};
