#include "mapmaker.h"
#include "Cell.h"
#include "raylib.h"
#include <queue>
#include <vector>
using namespace std;

Map *gmap = nullptr;

Cell *GetRandomCl() {
    int col = GetRandomValue(0, vc - 1);
    int row = GetRandomValue(0, hc - 1);
    return gmap->GetCell(row, col);
}

bool isSecPassed(float seconds) {
    static double previousTime = 0.0f;
    if (GetTime() - previousTime >= seconds) {
        previousTime = GetTime();
        return true;
    }
    return false;
}

bool isPath(int x, int y) {
    if (y >= hc || x >= vc || y < 0 || x < 0)
        return false;
    if (gmap->GetCell(y, x)->TileType == WALL)
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
            gmap->GetCell(s.y, s.x)->BackgroundColor = GREEN;
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

    gmap->SetPathColor(RED);
    gmap->ColorClSubList(Path);
    gmap->GetCell(to.y, to.x)->BackgroundColor = GOLD;
    gmap->SetPathColor(GREEN);
}

void makeWall(int x, int y) {
    gmap->GetCell(y, x)->TileType = WALL;
    gmap->GetCell(y, x)->BackgroundColor = BLACK;
}

void makePath(int x, int y) {
    gmap->GetCell(y, x)->TileType = ROAD;
    Color temp = BLACK;
    if (isEven(x + y)) {
        temp = BROWN;
    } else
        temp = WHITE;
    gmap->GetCell(y, x)->BackgroundColor = temp;
}

bool MouseInBoundries(Vector2 MousePos) {
    if (MousePos.x < WindowWidth && MousePos.y < WindowHeight && MousePos.y > 0 && MousePos.x > 0) {
        return true;
    } else
        return false;
}

template <typename T> void destroyByPtr(T **obj) {
    delete *obj;
    *obj = nullptr;
}

void mapMaker() {
    gmap = new Map();
    bool startRandomSearch = false;
    Vector2i source = {0, 0}, destination = {vc - 1, hc - 1};
    SetRandomSeed(GetTime());
    pacman *ahmed = new pacman();

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);
        gmap->Draw();
        ahmed->draw();
        if (IsWindowResized()) {
            WindowWidth = GetScreenWidth();
            WindowHeight = GetScreenHeight();
            gmap->Update();
        }
        if (IsKeyPressed(KEY_Q)) {
            goto Exit;
        }
        if (IsKeyPressed(KEY_R)) {
            for (int i = 0; i < hc; i++) {
                for (int j = 0; j < vc; j++) {
                    gmap->GetCell(i, j)->TileType = ROAD;
                }
            }
            source = {0, 0};
            destination = {vc - 1, hc - 1};
            gmap->ColorClList();
            startRandomSearch = false;
        }
        if (IsKeyPressed(KEY_S)) {
            source = {(int)(GetMouseX() / gmap->CellWidth), (int)(GetMouseY() / gmap->CellHeight)};
            gmap->GetCell(source.y, source.x)->BackgroundColor = ORANGE;
        }
        if (IsKeyPressed(KEY_D)) {
            destination = {(int)(GetMouseX() / gmap->CellWidth), (int)(GetMouseY() / gmap->CellHeight)};
            gmap->GetCell(destination.y, destination.x)->BackgroundColor = ORANGE;
        }
        if (IsKeyPressed(KEY_F) && !(IsKeyDown(KEY_RIGHT_SHIFT) || IsKeyDown(KEY_LEFT_SHIFT))) {
            findPath(source, destination);
        }
        if (IsKeyPressed(KEY_F) && (IsKeyDown(KEY_RIGHT_SHIFT) || IsKeyDown(KEY_LEFT_SHIFT))) {
            if (startRandomSearch) {
                startRandomSearch = false;
            } else
                startRandomSearch = true;
        }
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
                gmap->ColorClList();
                findPath(from->pos, to->pos);
            }
        }
        if (IsKeyDown(KEY_UP))
            ahmed->moveUp();
        if (IsKeyDown(KEY_DOWN))
            ahmed->moveDown();
        if (IsKeyDown(KEY_RIGHT))
            ahmed->moveRight();
        if (IsKeyDown(KEY_LEFT))
            ahmed->moveLeft();
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && MouseInBoundries(GetMousePosition())) {
            makeWall((int)(GetMouseX() / gmap->CellWidth), (int)(GetMouseY() / gmap->CellHeight));
        }
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT) && MouseInBoundries(GetMousePosition())) {
            makePath((int)(GetMouseX() / gmap->CellWidth), (int)(GetMouseY() / gmap->CellHeight));
        }
        EndDrawing();
    }
Exit:
    destroyByPtr(&gmap);
    destroyByPtr(&ahmed);
}

void mapMaker(Map *map) {
    gmap = map;
    Vector2i source = {0, 0}, destination = {vc - 1, hc - 1};
    bool startRandomSearch = false;
    SetRandomSeed(GetTime());

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);
        gmap->Draw();
        if (IsWindowResized()) {
            WindowWidth = GetScreenWidth();
            WindowHeight = GetScreenHeight();
            gmap->Update();
        }
        if (IsKeyPressed(KEY_Q)) {
            gmap->ColorClList();
            ClearBackground(WHITE);
            EndDrawing();
            break;
        }
        if (IsKeyPressed(KEY_R)) {
            for (int i = 0; i < hc; i++) {
                for (int j = 0; j < vc; j++) {
                    gmap->GetCell(i, j)->TileType = ROAD;
                }
            }
            source = {0, 0};
            destination = {vc - 1, hc - 1};
            gmap->ColorClList();
            startRandomSearch = false;
        }
        if (IsKeyPressed(KEY_S)) {
            source = {(int)(GetMouseX() / gmap->CellWidth), (int)(GetMouseY() / gmap->CellHeight)};
            gmap->GetCell(source.y, source.x)->BackgroundColor = ORANGE;
        }
        if (IsKeyPressed(KEY_D)) {
            destination = {(int)(GetMouseX() / gmap->CellWidth), (int)(GetMouseY() / gmap->CellHeight)};
            gmap->GetCell(destination.y, destination.x)->BackgroundColor = ORANGE;
        }
        if (IsKeyPressed(KEY_F) && !(IsKeyDown(KEY_RIGHT_SHIFT) || IsKeyDown(KEY_LEFT_SHIFT))) {
            findPath(source, destination);
        }
        if (IsKeyPressed(KEY_F) && (IsKeyDown(KEY_RIGHT_SHIFT) || IsKeyDown(KEY_LEFT_SHIFT))) {
            if (startRandomSearch) {
                startRandomSearch = false;
            } else
                startRandomSearch = true;
        }
        if (startRandomSearch && isSecPassed(0.1f)) {
            Cell *from = GetRandomCl();
            Cell *nWall = GetRandomCl();
            Cell *to = GetRandomCl();
            static int nWallCount = 0;
            if (!(from == nullptr || to == nullptr || nWall == nullptr)) {
                // continue;
                if (nWallCount <= (hc * vc) / 2) {
                    makeWall(nWall->pos.x, nWall->pos.y);
                    nWallCount++;
                }
                if (!(from->TileType == WALL || to->TileType == WALL)) {
                    gmap->ColorClList();
                    findPath(from->pos, to->pos);
                }
            }
        }
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && MouseInBoundries(GetMousePosition())) {
            makeWall((int)(GetMouseX() / gmap->CellWidth), (int)(GetMouseY() / gmap->CellHeight));
        }
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT) && MouseInBoundries(GetMousePosition())) {
            makePath((int)(GetMouseX() / gmap->CellWidth), (int)(GetMouseY() / gmap->CellHeight));
        }
        EndDrawing();
    }
    for (int i = 0; i < hc; i++) {
        for (int j = 0; j < vc; j++) {
            switch (map->GetCell(i, j)->TileType) {
            case (ROAD):
                map->GetCell(i, j)->BackgroundColor = BLACK;
                break;
            case (WALL):
                map->GetCell(i, j)->BackgroundColor = BLUE;
                break;
            }
        }
    }
}
