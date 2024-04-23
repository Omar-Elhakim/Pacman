#include "../Header_files/Level.h"
#include "../Header_files/Cell.h"
#include "../Header_files/mapmaker.h"
#include "../Header_files/pacman.h"
#include "../Header_files/food.h"
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
        ClearBackground(BLACK);
        map->Draw();
        pacman->draw();
        DrawText("Score : ", 10, map->infoBarHeight / 2 - 10, 30, WHITE);
        //====================
        food Food;
        Food.drawf();
        //=====================
        if (IsWindowResized()) {
            WindowWidth = GetScreenWidth();
            WindowHeight = GetScreenHeight();
            map->Update();
            pacman->setSize();
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
        if (IsKeyPressed(KEY_UP) || pacman->direction.y < 0) {
            pacman->goUp();
        }
        if (IsKeyPressed(KEY_DOWN) || pacman->direction.y > 0) {
            pacman->goDown();
        }
        if (IsKeyPressed(KEY_RIGHT) || pacman->direction.x > 0) {
            pacman->goRight();
        }
        if (IsKeyPressed(KEY_LEFT) || pacman->direction.x < 0) {
            pacman->goLeft();
        }
        EndDrawing();
    }
}
