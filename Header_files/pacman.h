#pragma once
#include "Food.h"
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
    Food *food;
    float scalFactor;

  public:
    Vector2 midpoint = { (InitialPosition.x + (map->CellWidth / 2)), (InitialPosition.y + (map->CellHeight / 2)) };
    Vector2 InitialPosition;
    Sound eat1;
    Sound eat2;
    Sound deathsound;
    int eatc = 0;
    int score;
    Vector2 direction;
    Pacman(Map *map, Food *food);
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
    void death();
};
