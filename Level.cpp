#include "Level.h"
#include "Cell.h"
#include "mapmaker.h"
#include "pacman.h"
#include "raylib.h"
#include<iostream>
#include "../Ghost.h"
using namespace std;

Level::Level(int WindowWidth, int WindowHeight) : WindowWidth(WindowWidth), WindowHeight(WindowHeight) {
    map = new Map();
    pacman = new Pacman(map);
    for (int i = 0; i < 3; ++i) {
        ghosts[i] = new Ghost(map);
        ghosts[i]->position = map->getClPos({ i,i+5 });
    }


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
        for (int i = 0; i < 3; ++i) {
            ghosts[i]->Draw();
        }
        DrawText("Score : ", 10, map->infoBarHeight / 2 - 10, 30, WHITE);
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



