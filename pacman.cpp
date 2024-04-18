#include "pacman.h"
#include "raylib.h"

pacman::pacman() {
    speed = 0.05f;
    x = 0;
    a = 0;

    pac = LoadImage("assets/pac.png");
    ImageResize(&pac, 80, 150);
    pacman1 = LoadTextureFromImage(pac);
    UnloadImage(pac);

    box = {0, 0, 40, 37};
    position = {150, 150};
    direction = {0, 0};
}

void pacman::draw() {
    DrawText("ana zhe2t <3", 150, 200, 50, DARKBLUE);
    DrawTextureRec(pacman1, box, position, WHITE);
}

void pacman::f() {
    if (IsKeyDown(KEY_RIGHT)) {
        direction = {0, 0};
        box.height = pac.height / 4.f;
        box.y = 0 * box.width;
        a++;
        if (a % 5 == 0) {
            x++;
        }
        if (x > 2)
            x = 0;
        box.x = x * box.width;
        direction.x += speed;
    }
    if (direction.x > 0) {
        box.height = pac.height / 4.f;
        box.y = 0 * box.width;
        a++;
        if (a % 250 == 0) {
            x++;
        }
        if (x > 2)
            x = 0;
        box.x = x * box.width;
    }

    if (IsKeyDown(KEY_LEFT)) {
        direction = {0, 0};
        box.height = pac.height / 4.f;
        box.y = 1 * box.width;
        a++;
        if (a % 250 == 0) {
            x++;
        }
        if (x > 2)
            x = 0;
        box.x = x * box.width;
        direction.x -= speed;
    }
    if (direction.x < 0) {
        box.height = pac.height / 4.f;
        box.y = 1 * box.width;
        a++;
        if (a % 250 == 0) {
            x++;
        }
        if (x > 2)
            x = 0;
        box.x = x * box.width;
    }

    if (IsKeyDown(KEY_UP)) {
        direction = {0, 0};
        box.height = pac.height / 4.f;
        box.y = 2 * box.width;
        a++;
        if (a % 250 == 0) {
            x++;
        }
        if (x > 2)
            x = 0;
        box.x = x * box.width;
        direction.y -= speed;
    }
    if (direction.y < 0) {
        box.height = pac.height / 4.f;
        box.y = 2 * box.width;
        a++;
        if (a % 250 == 0) {
            x++;
        }
        if (x > 2)
            x = 0;
        box.x = x * box.width;
    }

    if (IsKeyDown(KEY_DOWN)) {
        direction = {0, 0};
        box.height = pac.height / 5.f;
        box.y = 3 * box.width;
        a++;
        if (a % 250 == 0) {
            x++;
        }
        if (x > 2)
            x = 0;
        box.x = x * box.width;
        direction.y += speed;
    }
    if (direction.y > 0) {
        box.height = pac.height / 5.f;
        box.y = 3 * box.width;
        a++;
        if (a % 250 == 0) {
            x++;
        }
        if (x > 2)
            x = 0;
        box.x = x * box.width;
    }

    position.x += direction.x;
    position.y += direction.y;
}

void pacman::moveRight() {
    direction = {0, 0};
    box.height = pac.height / 4.f;
    box.y = 0 * box.width;
    a++;
    if (a % 5 == 0) {
        x++;
    }
    if (x > 2)
        x = 0;
    box.x = x * box.width;
    direction.x += speed;

    if (direction.x > 0) {
        box.height = pac.height / 4.f;
        box.y = 0 * box.width;
        a++;
        if (a % 250 == 0) {
            x++;
        }
        if (x > 2)
            x = 0;
        box.x = x * box.width;
    }

    position.x += direction.x;
    position.y += direction.y;
}

void pacman::moveLeft() {
    direction = {0, 0};
    box.height = pac.height / 4.f;
    box.y = 1 * box.width;
    a++;
    if (a % 250 == 0) {
        x++;
    }
    if (x > 2)
        x = 0;
    box.x = x * box.width;
    direction.x -= speed;

    if (direction.x < 0) {
        box.height = pac.height / 4.f;
        box.y = 1 * box.width;
        a++;
        if (a % 250 == 0) {
            x++;
        }
        if (x > 2)
            x = 0;
        box.x = x * box.width;
    }
    position.x += direction.x;
    position.y += direction.y;
}

void pacman::moveUp() {
    direction = {0, 0};
    box.height = pac.height / 4.f;
    box.y = 2 * box.width;
    a++;
    if (a % 250 == 0) {
        x++;
    }
    if (x > 2)
        x = 0;
    box.x = x * box.width;
    direction.y -= speed;
    if (direction.y < 0) {
        box.height = pac.height / 4.f;
        box.y = 2 * box.width;
        a++;
        if (a % 250 == 0) {
            x++;
        }
        if (x > 2)
            x = 0;
        box.x = x * box.width;
    }
    position.x += direction.x;
    position.y += direction.y;
}

void pacman::moveDown() {
    direction = {0, 0};
    box.height = pac.height / 5.f;
    box.y = 3 * box.width;
    a++;
    if (a % 250 == 0) {
        x++;
    }
    if (x > 2)
        x = 0;
    box.x = x * box.width;
    direction.y += speed;

    if (direction.y > 0) {
        box.height = pac.height / 5.f;
        box.y = 3 * box.width;
        a++;
        if (a % 250 == 0) {
            x++;
        }
        if (x > 2)
            x = 0;
        box.x = x * box.width;
    }

    position.x += direction.x;
    position.y += direction.y;
};

pacman::~pacman() {
    UnloadTexture(pacman1);
}
