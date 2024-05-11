#include "../Header_files/pacman.h"
#include "../Header_files/Level.h"
#include "raylib.h"

Pacman::Pacman(Map *map, Food *food) : map(map), food(food) {
    this->scalFactor = 0.80f;
    score = x = a = 0;
    speed = 1.8f;
    ImageSize = {2 * map->CellWidth * scalFactor, 4 * map->CellHeight * scalFactor};
    setSize();
    InitialPosition = map->getClPos(map->GetCell(1, 1)->arrPos);
    direction = {0, 0};
}

Pacman::Pacman(Map *map) : map(map) {
    speed = 1.8f;
    x = 0;
    a = 0;
    ImageSize = {2 * map->CellWidth * 0.95f, 4 * map->CellHeight * 0.95f};
    setSize();
    InitialPosition = map->getClPos(map->GetCell(0, 0)->arrPos);
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
    if (a % 9 == 0) x = (x + 1) % 3;
    AnimationBox.x = x * AnimationBox.width;
    InitialPosition.x += direction.x;
    InitialPosition.y += direction.y;
    // teleportaion:
    if (InitialPosition.x < -15)
        InitialPosition.x = WindowWidth;
    else if (InitialPosition.x >= WindowWidth)
        InitialPosition.x = 0;
}

void Pacman::eat() {
    Vector2 midpoint = {(InitialPosition.x + (map->CellWidth / 2)), (InitialPosition.y + (map->CellHeight / 2))};
    if ((midpoint.x < WindowWidth) && (midpoint.x > 0))
        if (map->GetCell(midpoint.x / map->CellWidth, (midpoint.y - map->infoBarHeight) / map->CellHeight)->hasFood ==
            true) {
            if (eatc % 2 == 0)
                PlaySound(eat1);
            else
                PlaySound(eat2);
            map->GetCell(midpoint.x / map->CellWidth, (midpoint.y - map->infoBarHeight) / map->CellHeight)->hasFood =
                false;
            score += 10;
            eatc++;
        }
}

void Pacman::goRight() {
    Vector2 pointerTL = {((InitialPosition.x + 1) / (map->CellWidth)) + 1, InitialPosition.y + 2};
    Vector2 pointerBR = {((InitialPosition.x + (map->CellWidth - 1)) / (map->CellWidth)) + 0.01,
                         InitialPosition.y + map->CellHeight - 2};
    direction = {speed, 0};
    AnimationBox.y = 0 * AnimationBox.height;
    if ((pointerTL.x < (WindowWidth / map->CellWidth)) && (pointerTL.x > 0) &&
        (pointerBR.x < (WindowWidth / map->CellWidth)) && (pointerBR.x > 0)) {
        if ((map->GetCell(pointerTL.x, (pointerTL.y - map->infoBarHeight) / map->CellHeight)->TileType == ROAD) &&
            (map->GetCell(pointerBR.x, (pointerBR.y - map->infoBarHeight) / map->CellHeight)->TileType == ROAD)) {
            move();
        }
    } else {
        move();
    }
}

void Pacman::goLeft() {
    Vector2 pointerTL = {((InitialPosition.x + 1) / (map->CellWidth)) - 0.01, InitialPosition.y + 2};
    Vector2 pointerBR = {((InitialPosition.x + (map->CellWidth - 1)) / (map->CellWidth)) - 1,
                         InitialPosition.y + map->CellHeight - 2};
    direction = {-1 * speed, 0};
    AnimationBox.y = 1 * AnimationBox.height;
    if ((pointerTL.x < (WindowWidth / map->CellWidth)) && (pointerTL.x > 0) &&
        (pointerBR.x < (WindowWidth / map->CellWidth)) && (pointerBR.x > 0)) {
        if ((map->GetCell(pointerTL.x, (pointerTL.y - map->infoBarHeight) / map->CellHeight)->TileType == ROAD) &&
            (map->GetCell(pointerBR.x, (pointerBR.y - map->infoBarHeight) / map->CellHeight)->TileType == ROAD)) {
            move();
        }
    } else {
        move();
    }
}

void Pacman::goUp() {
    Vector2 pointerTL = {InitialPosition.x + 1, InitialPosition.y + 2};
    Vector2 pointerBR = {InitialPosition.x + map->CellWidth - 1, InitialPosition.y + map->CellHeight - 2};
    direction = {0, -1 * speed};
    AnimationBox.y = 2 * AnimationBox.height;
    if ((map->GetCell(pointerTL.x / map->CellWidth, ((pointerTL.y - map->infoBarHeight) / map->CellHeight) - 0.01)
             ->TileType == ROAD) &&
        (map->GetCell(pointerBR.x / map->CellWidth, ((pointerBR.y - map->infoBarHeight) / map->CellHeight) - 1)
             ->TileType == ROAD)) {
        move();
    }
}

void Pacman::goDown() {
    Vector2 pointerTL = {InitialPosition.x + 1, InitialPosition.y + 2};
    Vector2 pointerBR = {InitialPosition.x + map->CellWidth - 1, InitialPosition.y + map->CellHeight - 2};
    direction = {0, speed};
    AnimationBox.y = 3 * AnimationBox.height;
    if ((map->GetCell(pointerTL.x / map->CellWidth, ((pointerTL.y - map->infoBarHeight) / map->CellHeight) + 1)
             ->TileType == ROAD) &&
        (map->GetCell(pointerBR.x / map->CellWidth, ((pointerBR.y - map->infoBarHeight) / map->CellHeight) + 0.01)
             ->TileType == ROAD)) {
        move();
    }
};

void Pacman::setSize() {
    PacmanImage = LoadImage("assets/pac2.png");
    Vector2 OldImageSize = ImageSize;
    eat1 = LoadSound("assets/chomp1.wav");
    eat2 = LoadSound("assets/chomp2.wav");
    // image size equalles 95% of cell size
    // it needs to change in movment functions
    ImageSize = {2 * map->CellWidth * scalFactor, 4 * map->CellHeight * scalFactor};
    // if window got resized change speed by the change ration of window size
    speed = 2.2f * (GetScreenHeight() + GetScreenWidth()) / (800 + 600);
    ImageResize(&PacmanImage, ImageSize.x, ImageSize.y);
    pacmanText = LoadTextureFromImage(PacmanImage);
    AnimationBox = {0, 0, PacmanImage.width / 2.f, PacmanImage.height / 4.f};
    UnloadImage(PacmanImage);
}
