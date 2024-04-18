#include "Level.h"
#include "Cell.h"
#include "mapmaker.h"
#include "pacman.h"
#include "raylib.h"

Level::Level(int WindowWidth, int WindowHeight) : WindowWidth(WindowWidth), WindowHeight(WindowHeight) {
    map = new Map();
    tebry = new pacman();
    source = {0, 0}, dest = {vc - 1, hc - 1};
}

Level::~Level() {
    delete map;
    delete tebry;
    map = nullptr;
    tebry = nullptr;
}

void Level::start() {
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);
        map->Draw();
        tebry->draw();
        if (IsWindowResized()) {
            WindowWidth = GetScreenWidth();
            WindowHeight = GetScreenHeight();
            map->Update();
        }
        if (IsKeyPressed(KEY_C)) {
            mapMaker(map);
        }
        if (IsKeyPressed(KEY_Q)) {
            EndDrawing();
            break;
        }
        if (IsKeyPressed(KEY_R)) {
            for (int i = 0; i < hc; i++) {
                for (int j = 0; j < vc; j++) {
                    map->GetCell(i, j)->TileType = ROAD;
                }
            }
            source = {0, 0};
            dest = {vc - 1, hc - 1};
            map->ColorClList();
        }
        if (IsKeyPressed(KEY_F) && !(IsKeyDown(KEY_RIGHT_SHIFT) || IsKeyDown(KEY_LEFT_SHIFT))) {
            map->FindPath(source, dest);
        }
        EndDrawing();
    }
}
