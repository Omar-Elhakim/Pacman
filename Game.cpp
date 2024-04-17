#include "Game.h"
#include "mapmaker.h"
#include "mapmaker.cpp"
#include "Window.h"
#include <queue>
#include "raylib.h"
Game::Game(int width,int height) :WindowWidth(width),WindowHeight(height)
{
    Window window = Window(WindowWidth, WindowHeight, "Mapmaker");
    cellLst = new CellList();
    Vector2i source = {0, 0}, destination = {vc - 1, hc - 1};
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        for (int i = 0; i < hc; i++) {
            for (int j = 0; j < vc; j++) {
                cellLst->getCell(i, j)->Draw();
            }
        }
        if (IsWindowResized()) {
            WindowWidth = GetScreenWidth();
            WindowHeight = GetScreenHeight();
            cellLst->Update();
        }
        if (IsKeyPressed(KEY_Q)) {
            break;
        }
        if (IsKeyPressed(KEY_R)) {
            for (int i = 0; i < hc; i++) {
                for (int j = 0; j < vc; j++) {
                    cellLst->getCell(i, j)->TileType = ROAD;
                }
            }
            source = {0, 0};
            destination = {vc - 1, hc - 1};
            cellLst->ColorClList();
        }
        if (IsKeyPressed(KEY_S)) {
            source = {(int)(GetMouseX() / cellLst->CellWidth), (int)(GetMouseY() / cellLst->CellHeight)};
            cellLst->getCell(source.y, source.x)->BackgroundColor = ORANGE;
        }
        if (IsKeyPressed(KEY_D)) {
            destination = {(int)(GetMouseX() / cellLst->CellWidth), (int)(GetMouseY() / cellLst->CellHeight)};
            cellLst->getCell(destination.y, destination.x)->BackgroundColor = ORANGE;
        }
        if (IsKeyPressed(KEY_F) && !(IsKeyDown(KEY_RIGHT_SHIFT) || IsKeyDown(KEY_LEFT_SHIFT))) {
            findPath(source, destination);
        }
        
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && MouseInBoundries(GetMousePosition())) {
            makeWall((int)(GetMouseX() / cellLst->CellWidth), (int)(GetMouseY() / cellLst->CellHeight));
        }
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT) && MouseInBoundries(GetMousePosition())) {
            makePath((int)(GetMouseX() / cellLst->CellWidth), (int)(GetMouseY() / cellLst->CellHeight));
        }
        EndDrawing();
    }
}

Game::~Game()
{

}