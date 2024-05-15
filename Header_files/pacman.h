#pragma once
#include "Cell.h"
#include "Food.h"
#include "Map.h"
#include "raylib.h"

class Pacman {
  private:
    Texture2D pacmanText;
    Rectangle AnimationBox;
    Vector2i ImageSize;
    int x;
    float speed;
    int a;
    Map *map;
    Food *food;
    float scaleFactor;
    Cell *currentCell();
    Cell *nextCell();
    bool CheckCollisionWall();
    bool CheckCollisionFood();
    void update();

  public:
    Vector2 InitialPosition;
    Sound eat1;
    Sound eat2;
    int eatc = 0;
    int score;
    Vector2i direction;
    Pacman(Map *map);
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
