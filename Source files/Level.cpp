#include "../Header files/Level.h"
#include "../Header files/Cell.h"
#include "../Header files/mapmaker.h"
#include "../Header files/pacman.h"
#include "raylib.h"

Level::Level(int WindowWidth, int WindowHeight) : WindowWidth(WindowWidth), WindowHeight(WindowHeight) {
    map = new Map();
    pacman = new Pacman(map);
    source = {0, 0}, dest = {vc - 1, hc - 1};
}

Level::~Level() {
    delete map;
    delete pacman;
    map = nullptr;
    pacman = nullptr;
}

void Level::start() {
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);
        map->Draw();
        pacman->draw();
        if (IsWindowResized()) {
            WindowWidth = GetScreenWidth();
            WindowHeight = GetScreenHeight();
            map->Update();
            pacman->update();
        }
        if (IsKeyPressed(KEY_C)) {
            mapMaker(map);
        }
        if (IsKeyPressed(KEY_Q)) {
            EndDrawing();
            break;
        }
        if (IsKeyPressed(KEY_F))
            map->FindPath(source, dest);
        if (IsKeyDown(KEY_UP) || pacman->direction.y < 0) {
            pacman->goUp();
        }
        if (IsKeyDown(KEY_DOWN) || pacman->direction.y > 0) {
            pacman->goDown();
        }
        if (IsKeyDown(KEY_RIGHT) || pacman->direction.x > 0) {
            pacman->goRight();
        }
        if (IsKeyDown(KEY_LEFT) || pacman->direction.x < 0) {
            pacman->goLeft();
        }
        EndDrawing();
    }
}
