#include "../Header_files/pacman.h"
#include "../Header_files/Level.h"
#include "../Header_files/VectorMath.h"
#include "raylib.h"

Pacman::Pacman(Map *map) : map(map) {
    scaleFactor = 0.80f;
    score = x = a = 0;
    speed = 11.f;
    setSize();
    InitialPosition = map->getClPos(map->GetCell({1, 1})->arrPos);
    direction = {0, 0};
    eat1 = LoadSound("assets/chomp1.wav");
    eat2 = LoadSound("assets/chomp2.wav");
}

Pacman::~Pacman() {
    UnloadSound(eat1);
    UnloadSound(eat2);
    UnloadTexture(pacmanText);
}

void Pacman::draw() {
    DrawTextureRec(pacmanText, AnimationBox, InitialPosition, WHITE);
}

void Pacman::eat() {
    Vector2 midpoint = {(InitialPosition.x + (map->CellWidth / 2)), (InitialPosition.y + (map->CellHeight / 2))};
    if (!((midpoint.x < WindowWidth) && (midpoint.x > 0))) return;
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

    // center pacman relative to the non changing axix
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
    Cell *nextCl = nextCell();
    if (!nextCl) return false;
    if (nextCl->TileType != WALL) return false;
    return CheckCollisionRecs(pacmanRect, nextCl->rec);
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
    ImageSize = V2toV2i(mulV2({2.f, 4.f}, scaleV2({map->CellWidth, map->CellHeight}, scaleFactor)));
    update();
    InitialPosition.x += (map->CellWidth - AnimationBox.x) / 2;
    InitialPosition.y += (map->CellHeight - AnimationBox.y) / 2;
}

void Pacman::update() {
    Vector2i OldImageSize = ImageSize;
    Image PacmanImage = LoadImage("assets/pac.png");
    ImageSize = V2toV2i(mulV2({2.f, 4.f}, scaleV2({map->CellWidth, map->CellHeight}, scaleFactor)));
    ImageResize(&PacmanImage, ImageSize.x, ImageSize.y);
    // image size equalles 95% of cell size
    // it needs to change in movment functions
    // if window got resized change speed by the change ration of window size
    pacmanText = LoadTextureFromImage(PacmanImage);
    AnimationBox = {0, 0, PacmanImage.width / 2.f, PacmanImage.height / 4.f};
    UnloadImage(PacmanImage);
    speed = 2.2f * (GetScreenHeight() + GetScreenWidth()) / (800 + 600);
}
