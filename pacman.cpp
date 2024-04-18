#include "pacman.h"
#include "raylib.h"

Pacman::Pacman() {
    speed = 1.5f;
    x = 0;
    a = 0;

    PacmanImage = LoadImage("assets/pac.png");
    ImageResize(&PacmanImage, 80, 150);
    pacmanText = LoadTextureFromImage(PacmanImage);
    UnloadImage(PacmanImage);

    AnimationBox = {0, 0, 40, 37};
    InitialPosition = {150, 150};
    direction = {0, 0};
}

void Pacman::draw() {
    DrawTextureRec(pacmanText, AnimationBox, InitialPosition, WHITE);
}

void Pacman::moveRight() {
    direction = {0, 0};
    AnimationBox.height = pacmanText.height / 4.f;
    AnimationBox.y = 0 * AnimationBox.width;
    a++;
    if (a % 5 == 0) {
        x++;
    }
    if (x > 2)
        x = 0;
    AnimationBox.x = x * AnimationBox.width;
    direction.x += speed;

    if (direction.x > 0) {
        AnimationBox.height = pacmanText.height / 4.f;
        AnimationBox.y = 0 * AnimationBox.width;
        a++;
        if (a % 250 == 0) {
            x++;
        }
        if (x > 2)
            x = 0;
        AnimationBox.x = x * AnimationBox.width;
    }

    InitialPosition.x += direction.x;
    InitialPosition.y += direction.y;
}

void Pacman::moveLeft() {
    direction = {0, 0};
    AnimationBox.height = pacmanText.height / 4.f;
    AnimationBox.y = 1 * AnimationBox.width;
    a++;
    if (a % 250 == 0) {
        x++;
    }
    if (x > 2)
        x = 0;
    AnimationBox.x = x * AnimationBox.width;
    direction.x -= speed;

    if (direction.x < 0) {
        AnimationBox.height = pacmanText.height / 4.f;
        AnimationBox.y = 1 * AnimationBox.width;
        a++;
        if (a % 250 == 0) {
            x++;
        }
        if (x > 2)
            x = 0;
        AnimationBox.x = x * AnimationBox.width;
    }
    InitialPosition.x += direction.x;
    InitialPosition.y += direction.y;
}

void Pacman::moveUp() {
    direction = {0, 0};
    AnimationBox.height = pacmanText.height / 4.f;
    AnimationBox.y = 2 * AnimationBox.width;
    a++;
    if (a % 250 == 0) {
        x++;
    }
    if (x > 2)
        x = 0;
    AnimationBox.x = x * AnimationBox.width;
    direction.y -= speed;
    if (direction.y < 0) {
        AnimationBox.height = pacmanText.height / 4.f;
        AnimationBox.y = 2 * AnimationBox.width;
        a++;
        if (a % 250 == 0) {
            x++;
        }
        if (x > 2)
            x = 0;
        AnimationBox.x = x * AnimationBox.width;
    }
    InitialPosition.x += direction.x;
    InitialPosition.y += direction.y;
}

void Pacman::moveDown() {
    direction = {0, 0};
    AnimationBox.height = pacmanText.height / 5.f;
    AnimationBox.y = 3 * AnimationBox.width;
    a++;
    if (a % 250 == 0) {
        x++;
    }
    if (x > 2)
        x = 0;
    AnimationBox.x = x * AnimationBox.width;
    direction.y += speed;

    if (direction.y > 0) {
        AnimationBox.height = pacmanText.height / 5.f;
        AnimationBox.y = 3 * AnimationBox.width;
        a++;
        if (a % 250 == 0) {
            x++;
        }
        if (x > 2)
            x = 0;
        AnimationBox.x = x * AnimationBox.width;
    }

    InitialPosition.x += direction.x;
    InitialPosition.y += direction.y;
};

Pacman::~Pacman() {
    UnloadTexture(pacmanText);
}
