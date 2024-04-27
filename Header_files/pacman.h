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
    Vector2 InitialPosition;
    int x;
    float speed;
    int a;
    Map *map;
    Food *food;

  public:
      int score1 = 0;
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
