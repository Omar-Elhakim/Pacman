#include "../Header_files/pacman.h"
#include "raylib.h"

Pacman::Pacman(Map *map) : map(map) {
    speed = 1.8f;
    x = 0;
    a = 0;
    ImageSize = {2 * map->CellWidth, 4 * map->CellHeight};
    setSize();
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
    Vector2 pointerTL = { InitialPosition.x + 3,InitialPosition.y + 6 };
    Vector2 pointerBR = { InitialPosition.x + map->CellWidth - 3,InitialPosition.y + map->CellHeight - 6 };
    direction = { speed, 0 };
    AnimationBox.y = 0 * AnimationBox.height;
    if ((map->GetCell(pointerTL.y / map->CellWidth, (pointerTL.x / map->CellHeight) + 1)->TileType == ROAD) && (map->GetCell(pointerBR.y / map->CellWidth, (pointerBR.x / map->CellHeight) + 0.01)->TileType == ROAD)) {
        move();
    }
}
 

void Pacman::goLeft() {
    Vector2 pointerTL = { InitialPosition.x + 3,InitialPosition.y + 6 };
    Vector2 pointerBR = { InitialPosition.x + map->CellWidth - 3,InitialPosition.y + map->CellHeight - 6 };
    direction = {-1 * speed, 0};
    AnimationBox.y = 1 * AnimationBox.height;
    if ((map->GetCell(pointerTL.y / map->CellWidth, (pointerTL.x / map->CellHeight)-0.01)->TileType == ROAD) && (map->GetCell(pointerBR.y / map->CellWidth, (pointerBR.x / map->CellHeight)-1)->TileType == ROAD)) {
        move();
    }
}

void Pacman::goUp() {
    Vector2 pointerTL = { InitialPosition.x + 3,InitialPosition.y + 6 };
    Vector2 pointerBR = { InitialPosition.x + map->CellWidth - 3,InitialPosition.y + map->CellHeight - 6 };
    direction = {0, -1 * speed};
    AnimationBox.y = 2 * AnimationBox.height;
    if ((map->GetCell((pointerTL.y / map->CellWidth)-0.01, pointerTL.x / map->CellHeight)->TileType == ROAD) && (map->GetCell((pointerBR.y / map->CellWidth) - 1, pointerBR.x / map->CellHeight)->TileType == ROAD)) {
        move();
    }
}

void Pacman::goDown() {
    Vector2 pointerTL = { InitialPosition.x + 3,InitialPosition.y + 6 };
    Vector2 pointerBR = { InitialPosition.x + map->CellWidth - 3,InitialPosition.y + map->CellHeight - 6 };
    direction = {0, speed};
    AnimationBox.y = 3 * AnimationBox.height;
    if ((map->GetCell((pointerTL.y / map->CellWidth) + 1, pointerTL.x / map->CellHeight)->TileType == ROAD) && (map->GetCell((pointerBR.y / map->CellWidth) + 0.01, pointerBR.x / map->CellHeight)->TileType == ROAD)) {
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
