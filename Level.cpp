#include "Level.h"
#include "Cell.h"
#include "mapmaker.h"
#include "pacman.h"
#include "raylib.h"

Level::Level(int WindowWidth, int WindowHeight) : WindowWidth(WindowWidth), WindowHeight(WindowHeight) {
    map = new Map();
    pacman = new Pacman();
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
        }
        if (IsKeyPressed(KEY_C)) {
            mapMaker(map);
        }
        if (IsKeyPressed(KEY_Q)) {
            EndDrawing();
            break;
        }
        if (IsKeyPressed(KEY_F))
            findPath(source, dest);
        if (IsKeyDown(KEY_UP)) {
            pacman->goUp();
        } else if (IsKeyDown(KEY_DOWN)) {
            pacman->goDown();
        } else if (IsKeyDown(KEY_RIGHT)) {
            pacman->goRight();
        } else if (IsKeyDown(KEY_LEFT)) {
            pacman->goLeft();
        } else
            pacman->move();
        EndDrawing();
    }
}
