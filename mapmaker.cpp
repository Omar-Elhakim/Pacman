#include "mapmaker.h"
#include "Cell.h"
#include "Window.h"
#include <queue>
#include <raylib.h>
#include <vector>

CellList *cellLst = nullptr;
int WindowWidth = 800, WindowHeight = 600;

Cell *GetRandomCl() {
    int col = GetRandomValue(0, vc - 1);
    int row = GetRandomValue(0, hc - 1);
    return cellLst->getCell(row, col);
}

bool isSecPassed(float seconds) {
    static double previousTime = 0.0f;
    if (GetTime() - previousTime >= seconds) {
        previousTime = GetTime();
        return true;
    }
    return false;
}

using namespace std;

bool isPath(int x, int y) {
    if (y >= hc || x >= vc || y < 0 || x < 0)
        return false;
    if (cellLst->getCell(y, x)->TileType == WALL)
        return false;
    return true;
}

void BFS(Vector2i prev[hc][vc], Vector2i from) {
    int row = from.y, col = from.x;
    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};
    queue<Vector2i> TN;
    TN.push(from);

    bool visited[hc][vc];
    for (int i = 0; i < hc; i++)
        for (int j = 0; j < vc; j++)
            visited[i][j] = false;

    visited[row][col] = true;
    while (!TN.empty()) {
        Vector2i s = TN.front();
        for (int i = 0; i < 4; i++) {
            col = s.x + dc[i];
            row = s.y + dr[i];
            cellLst->getCell(s.y, s.x)->BackgroundColor = GREEN;
            if (isPath(col, row) && !visited[row][col]) {
                visited[row][col] = true;
                prev[row][col] = s;
                TN.push({col, row});
            }
        }
        TN.pop();
    }
}

void findPath(Vector2i from, Vector2i to) {
    vector<Vector2i> Path;
    Vector2i prev[hc][vc];
    for (int i = 0; i < hc; i++)
        for (int j = 0; j < vc; j++)
            prev[i][j] = {-1, -1};

    BFS(prev, from);
    Vector2i temp = to;
    int row = temp.y, col = temp.x;

    do {
        row = temp.y;
        col = temp.x;
        Path.push_back(temp);
        temp = prev[row][col];
    } while (prev[row][col].x != -1);

    cellLst->SetPathColor(RED);
    cellLst->ColorClSubList(Path);
    cellLst->getCell(to.y, to.x)->BackgroundColor = GOLD;
    cellLst->SetPathColor(GREEN);
}

void makeWall(int x, int y) {
    cellLst->getCell(y, x)->TileType = WALL;
    cellLst->getCell(y, x)->BackgroundColor = BLACK;
}

void makePath(int x, int y) {
    cellLst->getCell(y, x)->TileType = ROAD;
    Color temp = BLACK;
    if (isEven(x + y)) {
        temp = BROWN;
    } else
        temp = WHITE;
    cellLst->getCell(y, x)->BackgroundColor = temp;
}

bool MouseInBoundries(Vector2 MousePos) {
    if (MousePos.x < WindowWidth && MousePos.y < WindowHeight && MousePos.y > 0 && MousePos.x > 0) {
        return true;
    } else
        return false;
}

void game() {
    Window window = Window(WindowWidth, WindowHeight, "Mapmaker");
    cellLst = new CellList();
    bool startRandomSearch = false;
    Vector2i source = { 0,0 }, destination = { vc - 1,hc - 1 };
    SetRandomSeed(GetTime());
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        for (int i = 0; i < hc; i++) {
            for (int j = 0; j < vc; j++) {
                cellLst->getCell(i, j)->Draw();
            }
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
            source = { 0,0 };
            destination = { vc - 1,hc - 1 };
            cellLst->ColorClList();
            startRandomSearch = false;
        }
        if (IsWindowResized()) {
            WindowWidth = GetScreenWidth();
            WindowHeight = GetScreenHeight();
            cellLst->Update();
        }
        if (IsKeyPressed(KEY_S)) {
            source = { (int)(GetMouseX() / cellLst->CellWidth), (int)(GetMouseY() / cellLst->CellHeight) };
            cellLst->getCell(source.y,source.x)->BackgroundColor = ORANGE;

        }
        if (IsKeyPressed(KEY_D)) {
            destination = { (int)(GetMouseX() / cellLst->CellWidth), (int)(GetMouseY() / cellLst->CellHeight) };
            cellLst->getCell(destination.y, destination.x)->BackgroundColor = ORANGE;
        }
        if (IsKeyPressed(KEY_F)) {
            findPath(source, destination);
            //startRandomSearch = true;
        }
        /*
        if (startRandomSearch && isSecPassed(0.1f)) {
            Cell *from = GetRandomCl();
            Cell *nWall = GetRandomCl();
            Cell *to = GetRandomCl();
            static int nWallCount = 0;
            if (from == nullptr || to == nullptr || nWall == nullptr) {
                continue;
            }
            if (nWallCount <= (hc * vc) / 2) {
                makeWall(nWall->pos.x, nWall->pos.y);
                nWallCount++;
            }
            if (!(from->TileType == WALL || to->TileType == WALL)) {
                cellLst->ColorClList();
                findPath(from->pos, to->pos);
            }
        }*/
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && MouseInBoundries(GetMousePosition())) {
            makeWall((int)(GetMouseX() / cellLst->CellWidth), (int)(GetMouseY() / cellLst->CellHeight));
        }
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT) && MouseInBoundries(GetMousePosition())) {
            makePath((int)(GetMouseX() / cellLst->CellWidth), (int)(GetMouseY() / cellLst->CellHeight));
        }
        EndDrawing();
    }
}
