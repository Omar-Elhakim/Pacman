#include "pacman.h"
#include "raylib.h"

pacman::pacman() {
    speed = 1.5f;
    x = 0;
    a = 0;

    PacmanImage = LoadImage("assets/pac.png");
    ImageResize(&PacmanImage, 80, 150);
    Pacman = LoadTextureFromImage(PacmanImage);
    UnloadImage(PacmanImage);

    AnimationBox = {0, 0, 40, 37};
    InitialPosition = {150, 150};
    direction = {0, 0};
}

void pacman::draw() {
    DrawTextureRec(Pacman, AnimationBox, InitialPosition, WHITE);
}

void pacman::moveRight() {
    direction = {0, 0};
    AnimationBox.height = Pacman.height / 4.f;
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
        AnimationBox.height = Pacman.height / 4.f;
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

void pacman::moveLeft() {
    direction = {0, 0};
    AnimationBox.height = Pacman.height / 4.f;
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
        AnimationBox.height = Pacman.height / 4.f;
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

void pacman::moveUp() {
    direction = {0, 0};
    AnimationBox.height = Pacman.height / 4.f;
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
        AnimationBox.height = Pacman.height / 4.f;
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

void pacman::moveDown() {
    direction = {0, 0};
    AnimationBox.height = Pacman.height / 5.f;
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
        AnimationBox.height = Pacman.height / 5.f;
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

pacman::~pacman() {
    UnloadTexture(Pacman);
}
