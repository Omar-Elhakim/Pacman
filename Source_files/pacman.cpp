#include "../Header_files/pacman.h"
#include "raylib.h"

Pacman::Pacman(Map *map) : map(map) {
    speed = 1.7f;
    x = 0;
    a = 0;
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
    InitialPosition.x += direction.x;
    InitialPosition.y += direction.y;
}

void Pacman::goRight() {
    direction = {0, 0};
    AnimationBox.y = 0 * AnimationBox.width;
    a++;
    if (a % 10 == 0) {
        x++;
    }
    if (x > 2)
        x = 0;
    AnimationBox.x = x * AnimationBox.width;
    direction.x += speed;

    if (direction.x > 0) {
        AnimationBox.y = 0 * AnimationBox.width;
        a++;
        if (a % 10 == 0) {
            x++;
        }
        if (x > 2)
            x = 0;
        AnimationBox.x = x * AnimationBox.width;
    }
    move();
}

void Pacman::goLeft() {
    direction = {0, 0};
    AnimationBox.y = 1 * AnimationBox.width;
    a++;
    if (a % 10 == 0) {
        x++;
    }
    if (x > 2)
        x = 0;
    AnimationBox.x = x * AnimationBox.width;
    direction.x -= speed;

    if (direction.x < 0) {
        AnimationBox.y = 1 * AnimationBox.width;
        a++;
        if (a % 10 == 0) {
            x++;
        }
        if (x > 2)
            x = 0;
        AnimationBox.x = x * AnimationBox.width;
    }
    move();
}

void Pacman::goUp() {
    direction = {0, 0};
    AnimationBox.y = 2 * AnimationBox.width;
    a++;
    if (a % 10 == 0) {
        x++;
    }
    if (x > 2)
        x = 0;
    AnimationBox.x = x * AnimationBox.width;
    direction.y -= speed;
    if (direction.y < 0) {
        AnimationBox.y = 2 * AnimationBox.width;
        a++;
        if (a % 10 == 0) {
            x++;
        }
        if (x > 2)
            x = 0;
        AnimationBox.x = x * AnimationBox.width;
    }
    move();
}

void Pacman::goDown() {
    direction = {0, 0};
    AnimationBox.y = 3 * AnimationBox.width;
    a++;
    if (a % 10 == 0) {
        x++;
    }
    if (x > 2)
        x = 0;
    AnimationBox.x = x * AnimationBox.width;
    direction.y += speed;

    if (direction.y > 0) {
        AnimationBox.y = 3 * AnimationBox.width;
        a++;
        if (a % 10 == 0) {
            x++;
        }
        if (x > 2)
            x = 0;
        AnimationBox.x = x * AnimationBox.width;
    }
    move();
};

void Pacman::setSize() {
    PacmanImage = LoadImage("assets/pac.png");
    ImageSize = {2 * map->CellWidth, 4 * map->CellHeight};
    ImageResize(&PacmanImage, ImageSize.x, ImageSize.y);

    pacmanText = LoadTextureFromImage(PacmanImage);
    UnloadImage(PacmanImage);

    // TODO : doesn't update succeffuly
    AnimationBox = {0, 0, pacmanText.width / 2.f, pacmanText.height / 4.f};
}
