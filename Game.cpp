#include "Game.h"
#include "mapmaker.h"
#include "Window.h"
#include "Cell.h"
#include <queue>
#include "raylib.h"
#include <iostream>

Game::Game(int width,int height) :WindowWidth(width),WindowHeight(height)
{
    notgame();
    }

void Game::notgame() {
    Window window = Window(WindowWidth, WindowHeight, "Mapmaker");
    CellList* cellLst2;

    cellLst2 = new CellList();
    Vector2i source = { 0, 0 }, destination = { vc - 1, hc - 1 };
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        for (int i = 0; i < hc; i++) {
            for (int j = 0; j < vc; j++) {
                cellLst2->getCell(i, j)->Draw();
            }
        }
        if (IsWindowResized()) {
            WindowWidth = GetScreenWidth();
            WindowHeight = GetScreenHeight();
            cellLst2->Update();
        }
        if (IsKeyPressed(KEY_Q)) {
            break;
        }
        if (IsKeyPressed(KEY_R)) {
            for (int i = 0; i < hc; i++) {
                for (int j = 0; j < vc; j++) {
                    cellLst2->getCell(i, j)->TileType = ROAD;
                }
            }
            source = { 0, 0 };
            destination = { vc - 1, hc - 1 };
            cellLst2->ColorClList();
        }
        if (IsKeyPressed(KEY_S)) {
            source = { (int)(GetMouseX() / cellLst2->CellWidth), (int)(GetMouseY() / cellLst2->CellHeight) };
            cellLst2->getCell(source.y, source.x)->BackgroundColor = ORANGE;
        }
        if (IsKeyPressed(KEY_D)) {
            destination = { (int)(GetMouseX() / cellLst2->CellWidth), (int)(GetMouseY() / cellLst2->CellHeight) };
            cellLst2->getCell(destination.y, destination.x)->BackgroundColor = ORANGE;
        }
        if (IsKeyPressed(KEY_F) && !(IsKeyDown(KEY_RIGHT_SHIFT) || IsKeyDown(KEY_LEFT_SHIFT))) {
            findPath(source, destination);
        }
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && MouseInBoundries(GetMousePosition())) {
            makeWall((int)(GetMouseX() / cellLst2->CellWidth), (int)(GetMouseY() / cellLst2->CellHeight));
        }
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT) && MouseInBoundries(GetMousePosition())) {
            makePath((int)(GetMouseX() / cellLst2->CellWidth), (int)(GetMouseY() / cellLst2->CellHeight));
        }
        EndDrawing();
    }
}
Game::~Game()
{

}