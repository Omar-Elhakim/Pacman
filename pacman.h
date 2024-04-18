#pragma once
#include "raylib.h"
#include <cmath>

class pacman {
private:
    Image PacmanImage;
    Rectangle AnimationBox;
    Vector2 InitialPosition;
    Vector2 direction;
    float x;
    int a;

public:
    pacman();
    ~pacman();
    Texture2D Pacman;
    float speed;
    void draw();
    void moveRight();
    void moveLeft();
    void moveUp();
    void moveDown();
};
