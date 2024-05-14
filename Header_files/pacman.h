#pragma once
#include "Cell.h"
#include "Food.h"
#include "Map.h"
#include "raylib.h"

class Pacman {
  private:
    Image PacmanImage;
    Texture2D pacmanText;
    Rectangle AnimationBox;
    Vector2i ImageSize;
    int x;
    float speed;
    int a;
    Map *map;
    Food *food;
    float scalFactor;

  public:
    Vector2 InitialPosition;
    Sound eat1;
    Sound eat2;
    int eatc = 0;
    int score;
    Vector2i direction;
    Pacman(Map *map, Food *food);
    Pacman(Map *map);
    ~Pacman();
    bool CheckCollisionWall(Rectangle wall,Vector2i direction);
    bool CheckCollisionFood(Vector2 foodCenter);
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
