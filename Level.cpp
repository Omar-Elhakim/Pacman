#include "Level.h"
#include "Cell.h"
#include "mapmaker.h"
#include "pacman.h"
#include "raylib.h"

Level::Level(int WindowWidth, int WindowHeight) : WindowWidth(WindowWidth), WindowHeight(WindowHeight) {
    map = new Map();
    source = {0, 0}, dest = {vc - 1, hc - 1};
    tebry = pacman();
}

void Level::notgame() {
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);
        map->draw();
        tebry.draw();
        if (IsWindowResized()) {
            WindowWidth = GetScreenWidth();
            WindowHeight = GetScreenHeight();
            map->Update();
        }
        if (IsKeyPressed(KEY_Q)) {
            EndDrawing();
            break;
        }
        if (IsKeyPressed(KEY_R)) {
            for (int i = 0; i < hc; i++) {
                for (int j = 0; j < vc; j++) {
                    map->getCell(i, j)->TileType = ROAD;
                }
            }
            source = {0, 0};
            dest = {vc - 1, hc - 1};
            map->ColorClList();
        }
        if (IsKeyPressed(KEY_S)) {
            source = {(int)(GetMouseX() / map->CellWidth), (int)(GetMouseY() / map->CellHeight)};
            map->getCell(source.y, source.x)->BackgroundColor = ORANGE;
        }
        if (IsKeyPressed(KEY_D)) {
            dest = {(int)(GetMouseX() / map->CellWidth), (int)(GetMouseY() / map->CellHeight)};
            map->getCell(dest.y, dest.x)->BackgroundColor = ORANGE;
        }
        if (IsKeyPressed(KEY_F) && !(IsKeyDown(KEY_RIGHT_SHIFT) || IsKeyDown(KEY_LEFT_SHIFT))) {
            findPath(source, dest);
        }
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && MouseInBoundries(GetMousePosition())) {
            makeWall((int)(GetMouseX() / map->CellWidth), (int)(GetMouseY() / map->CellHeight));
        }
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT) && MouseInBoundries(GetMousePosition())) {
            makePath((int)(GetMouseX() / map->CellWidth), (int)(GetMouseY() / map->CellHeight));
        }
        EndDrawing();
    }
}

Level::~Level() {
}
