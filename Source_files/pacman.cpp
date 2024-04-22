#include "../Header_files/pacman.h"
#include "raylib.h"

Pacman::Pacman(Map *map) : map(map) {
    speed = 1.7f;
    x = 0;
    a = 0;
    ImageSize = {2 * map->CellWidth, 4 * map->CellHeight};
    setSize();

    InitialPosition = map->getClPos({1, 1});
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
    if (a % 10 == 0)
        x = (x + 1) % 3;
    AnimationBox.x = x * AnimationBox.width;
    InitialPosition.x += direction.x;
    InitialPosition.y += direction.y;
}

void Pacman::goRight() {
    direction = {speed, 0};
    AnimationBox.y = 0 * AnimationBox.height;
    move();
}

void Pacman::goLeft() {
    direction = {-1 * speed, 0};
    AnimationBox.y = 1 * AnimationBox.height;
    move();
}

void Pacman::goUp() {
    direction = {0, -1 * speed};
    AnimationBox.y = 2 * AnimationBox.height;
    move();
}

void Pacman::goDown() {
    direction = {0, speed};
    AnimationBox.y = 3 * AnimationBox.height;
    move();
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
