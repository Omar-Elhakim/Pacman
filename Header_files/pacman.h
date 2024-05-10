#pragma once
#include "Map.h"
#include "raylib.h"
#include "Food.h"

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
    Food *food;

  public:
    Vector2 InitialPosition;
    Sound eat1;
    Sound eat2;
    int eatc = 0;
    int score;
    Vector2 direction;
    Pacman(Map *map, Food* food);
    Pacman(Map* map);
    ~Pacman();
    void draw();
    void move();
    void goRight();
    void goLeft();
    void goUp();
    void goDown();
    void setSize();
    void eat();
    void die();
};
