#include "../Header_files/Level.h"
#include "../Header_files/Cell.h"
#include "../Header_files/mapmaker.h"
#include "../Header_files/pacman.h"
#include "../Header_files/Ghost.h"
#include "raylib.h"
#include<iostream>
using namespace std;



Level::Level(int WindowWidth, int WindowHeight) : WindowWidth(WindowWidth), WindowHeight(WindowHeight) {
    map = new Map();
    food = new Food(map);
    pacman = new Pacman(map,food);
    ghosts = new Ghost(map);
    source = {0, 0}, dest = {vc - 1, hc - 1};

}

Level::~Level() {
    delete map;
    delete pacman;
    delete ghosts;
    map = nullptr;
    pacman = nullptr;
    ghosts = nullptr;
}

void Level::start() {
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        map->Draw();
        food->draw(map);
        pacman->draw();
        ghosts->draw();
        DrawText(TextFormat("Counter: %d", pacman->score1), 10, map->infoBarHeight / 2 - 10, 30, WHITE);
        if (IsWindowResized()) {
            WindowWidth = GetScreenWidth();
            WindowHeight = GetScreenHeight();
            map->Update();
            pacman->setSize();
        }
        if (IsKeyPressed(KEY_C)) {
            mapMaker(map);
            food->update(map);

        }
        if (IsKeyPressed(KEY_Q)) {
            EndDrawing();
            break;
        }
        if (IsKeyPressed(KEY_F))
            map->FindPath(source, dest);
        if (IsKeyPressed(KEY_UP) || pacman->direction.y < 0) {
            pacman->goUp();
            pacman->eat();
        }
        if (IsKeyPressed(KEY_DOWN) || pacman->direction.y > 0) {
            pacman->goDown();
            pacman->eat();
        }
        if (IsKeyPressed(KEY_RIGHT) || pacman->direction.x > 0) {
            pacman->goRight();
            pacman->eat();
        }
        if (IsKeyPressed(KEY_LEFT) || pacman->direction.x < 0) {
            pacman->goLeft();
            pacman->eat();
        }
        
        EndDrawing();
    }
}
