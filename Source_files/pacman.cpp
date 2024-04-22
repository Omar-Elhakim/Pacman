#include "../Header_files/pacman.h"
#include "raylib.h"

Pacman::Pacman(Map *map) : map(map) {
    speed = 1.8f;
    x = 0;
    a = 0;
    ImageSize = {2 * map->CellWidth, 4 * map->CellHeight};
    setSize();
    //{ 150,150};
    InitialPosition =  map->getClPos(map->GetCell(0, 0)->arrPos);
    direction = {0, 0};
}

Pacman::~Pacman() {
    UnloadTexture(pacmanText);
}

void Pacman::draw() {
    DrawTextureRec(pacmanText, AnimationBox, InitialPosition, WHITE);
}

void Pacman::move() {
    a++;
    if (a % 9 == 0)
        x = (x + 1) % 3;
    AnimationBox.x = x * AnimationBox.width;
    InitialPosition.x += direction.x;
    InitialPosition.y += direction.y;
}

void Pacman::goRight() {
    Vector2 pointer = { InitialPosition.x + map->CellWidth -5,InitialPosition.y + map->CellHeight -5};
    direction = {speed, 0};
    AnimationBox.y = 0 * AnimationBox.height;
   //if ((map->GetCell(InitialPosition.y / map->CellWidth, (InitialPosition.x / map->CellHeight) +1)->TileType == ROAD) && (map->GetCell(pointer.y / map->CellWidth, (pointer.x / map->CellHeight)+0.1)->TileType == ROAD)) {
   if((map->GetCell(InitialPosition.y / map->CellWidth, (InitialPosition.x / map->CellHeight) +1)->TileType == WALL) && CheckCollisionRecs(AnimationBox, map->GetCell(InitialPosition.y / map->CellWidth, (InitialPosition.x / map->CellHeight) + 1)->rec)){
       printf("road");
   }
    else 
        move();
    }

void Pacman::goLeft() {
    Vector2 pointer = { InitialPosition.x + map->CellWidth -5,InitialPosition.y + map->CellHeight -5};
    direction = {-1 * speed, 0};
    AnimationBox.y = 1 * AnimationBox.height;
    if ((map->GetCell(InitialPosition.y / map->CellWidth, (InitialPosition.x / map->CellHeight)-0.1)->TileType == ROAD) && (map->GetCell(pointer.y / map->CellWidth, (pointer.x / map->CellHeight)-1)->TileType == ROAD)) {
        move();
    }
}

void Pacman::goUp() {
    Vector2 pointer = { InitialPosition.x + map->CellWidth -5,InitialPosition.y + map->CellHeight -5};
    direction = {0, -1 * speed};
    AnimationBox.y = 2 * AnimationBox.height;
    if ((map->GetCell((InitialPosition.y / map->CellWidth)-0.1,InitialPosition.x / map->CellHeight)->TileType == ROAD) && (map->GetCell((pointer.y / map->CellWidth) - 1, pointer.x / map->CellHeight)->TileType == ROAD)) {
        move();
    }
}

void Pacman::goDown() {
    Vector2 pointer = { InitialPosition.x + map->CellWidth -5,InitialPosition.y + map->CellHeight -5};
    direction = {0, speed};
    AnimationBox.y = 3 * AnimationBox.height;
    if ((map->GetCell((InitialPosition.y / map->CellWidth) + 1,InitialPosition.x / map->CellHeight)->TileType == ROAD) && (map->GetCell((pointer.y / map->CellWidth) + 0.1, pointer.x / map->CellHeight)->TileType == ROAD)) {
        move();
    }
};

void Pacman::setSize() {
    PacmanImage = LoadImage("assets/pac.png");
    Vector2 OldImageSize = ImageSize;
    ImageSize = {2 * map->CellWidth, 4 * map->CellHeight};
    speed *= (ImageSize.x * ImageSize.y) / (OldImageSize.x * OldImageSize.y);
    ImageResize(&PacmanImage, ImageSize.x, ImageSize.y);
    pacmanText = LoadTextureFromImage(PacmanImage);
    AnimationBox = {0, 0, PacmanImage.width / 2.f, pacmanText.height / 4.f};
    UnloadImage(PacmanImage);
}
