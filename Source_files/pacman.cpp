#include "../Header_files/pacman.h"
#include "../Header_files/Level.h"
#include "../Header_files/VectorMath.h"
#include "raylib.h"

Pacman::Pacman(Map *map) : map(map) {
    this->scaleFactor = 0.80f;
    score = x = a = 0;
    speed = 10.8f;
    ImageSize = {(int)(2 * map->CellWidth * scaleFactor), (int)(4 * map->CellHeight * scaleFactor)};
    setSize();
    InitialPosition = map->getClPos(map->GetCell({1, 1})->arrPos);
    direction = {0, 0};
}

Pacman::~Pacman() {
    UnloadTexture(pacmanText);
}

void Pacman::draw() {
    DrawTextureRec(pacmanText, AnimationBox, InitialPosition, WHITE);
}

void Pacman::eat() {
    Vector2 midpoint = {(InitialPosition.x + (map->CellWidth / 2)), (InitialPosition.y + (map->CellHeight / 2))};
    if ((midpoint.x < WindowWidth) && (midpoint.x > 0))
        if (map->GetCell(map->getClArrPos(midpoint))->hasFood == true) {
            if (eatc % 2 == 0)
                PlaySound(eat1);
            else
                PlaySound(eat2);
            map->GetCell(map->getClArrPos(midpoint))->hasFood = false;
            score += 10;
            eatc++;
        }
}

Cell *Pacman::currentCell() {
    Vector2 pacmanMidpoint = {
        (InitialPosition.x + (map->CellWidth / 2)),
        (InitialPosition.y + (map->CellHeight / 2)),
    };
    return map->GetCell(map->getClArrPos(pacmanMidpoint));
}

Cell *Pacman::nextCell() {
    Cell *current = currentCell();
    if (!current) return nullptr;
    Vector2i nextArrPos = sumV2i(current->arrPos, direction);
    return map->GetCell(nextArrPos);
}

void Pacman::move() {
    a++;
    if (a % 9 == 0) x = (x + 1) % 3;
    AnimationBox.x = x * AnimationBox.width;

    if (CheckCollisionWall()) return;

    if (currentCell()) {
        if (direction.x != 0) InitialPosition.y = currentCell()->getCenter().y - AnimationBox.width / 2;
        if (direction.y != 0) InitialPosition.x = currentCell()->getCenter().x - AnimationBox.height / 2;
    }

    InitialPosition.x += direction.x * speed;
    InitialPosition.y += direction.y * speed;

    // teleportaion:
    if (InitialPosition.x <= -map->CellWidth)
        InitialPosition.x = WindowWidth;
    else if (InitialPosition.x >= WindowWidth)
        InitialPosition.x = -map->CellWidth;
}

bool Pacman::CheckCollisionWall() {
    Rectangle pacmanRect = {
        InitialPosition.x + (direction.x * speed),
        InitialPosition.y + (direction.y * speed),
        (float)AnimationBox.width,
        (float)AnimationBox.height,
    };
    bool res = false;
    Cell *nextCheck = nullptr, *nextCl = nextCell();
    int dir[] = {-1, 0, 1};

    if (!nextCl) return res;
    // if there is collision then don't continue the loop to not change the res value;
    for (int i = 0; i < 3 && !res; i++) {
        if (direction.x == 0) {
            nextCheck = map->GetCell(sumV2i(nextCl->arrPos, {dir[i], 0}));
        } else
            nextCheck = map->GetCell(sumV2i(nextCl->arrPos, {0, dir[i]}));
        if (!nextCheck) continue;
        if (nextCheck->TileType != WALL) continue;
        res = CheckCollisionRecs(pacmanRect, nextCheck->rec);
    }
    return res;
}

void Pacman::goRight() {
    direction = {1, 0};
    AnimationBox.y = 0 * AnimationBox.height;
}

void Pacman::goLeft() {
    direction = {-1, 0};
    AnimationBox.y = 1 * AnimationBox.height;
}

void Pacman::goUp() {
    direction = {0, -1};
    AnimationBox.y = 2 * AnimationBox.height;
}

void Pacman::goDown() {
    direction = {0, 1};
    AnimationBox.y = 3 * AnimationBox.height;
};

void Pacman::setSize() {
    // Vector2i OldImageSize = ImageSize;
    PacmanImage = LoadImage("assets/pac.png");
    ImageSize = {(int)(2 * map->CellWidth * scaleFactor), (int)(4 * map->CellHeight * scaleFactor)};
    ImageResize(&PacmanImage, ImageSize.x, ImageSize.y);
    eat1 = LoadSound("assets/chomp1.wav");
    eat2 = LoadSound("assets/chomp2.wav");
    // image size equalles 95% of cell size
    // it needs to change in movment functions
    // if window got resized change speed by the change ration of window size
    speed = 2.2f * (GetScreenHeight() + GetScreenWidth()) / (800 + 600);
    pacmanText = LoadTextureFromImage(PacmanImage);
    AnimationBox = {0, 0, PacmanImage.width / 2.f, PacmanImage.height / 4.f};
    InitialPosition.x += (map->CellWidth - AnimationBox.x) / 2;
    InitialPosition.y += (map->CellHeight - AnimationBox.y) / 2;
    UnloadImage(PacmanImage);
}
