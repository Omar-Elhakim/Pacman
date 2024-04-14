#include "mapmaker.h"
#include "Window.h"
#include <queue>
#include <vector>

CellList *cellLst = nullptr;
int WindowWidth = 800, WindowHeight = 600;

using namespace std;

int main() {
    game();
    return 0;
}

bool isPath(int x, int y) {
    if (y >= hc || x >= vc || y < 0 || x < 0)
        return false;
    if (cellLst->getCell(y, x)->TileType == WALL)
        return false;
    return true;
}

void BFS(Vector2i prev[hc][vc], Vector2i from) {
    int row = 0, col = 0;
    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};
    queue<Vector2i> TN;
    TN.push(from);

    bool visited[hc][vc];
    for (int i = 0; i < hc; i++)
        for (int j = 0; j < vc; j++)
            visited[i][j] = false;

    visited[from.y][from.x] = true;
    while (!TN.empty()) {
        Vector2i s = TN.front();
        for (int i = 0; i < 4; i++) {
            col = s.x + dc[i];
            row = s.y + dr[i];
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
    cellLst->SetPathColor(GREEN);
}

void makeWall(int x, int y) {
    // cellLst->getCell(y, x)->
    cellLst->getCell(y, x)->TileType = WALL;
    cellLst->getCell(y, x)->BackgroundColor = BLACK;
}

void makePath(int x, int y) {
    cellLst->getCell(y, x)->TileType = PATH;
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
    Window window = Window(WindowWidth, WindowHeight, "mapmaker");
    cellLst = new CellList();
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
            cellLst->ColorClList();
            for (int i = 0; i < hc; i++) {
                for (int j = 0; j < vc; j++) {
                    cellLst->getCell(i, j)->TileType = PATH;
                }
            }
        }
        if (IsWindowResized()) {
            WindowWidth = GetScreenWidth();
            WindowHeight = GetScreenHeight();
            cellLst->Update();
        }

        if (IsKeyPressed(KEY_F)) {
            findPath({0, 0}, {vc - 1, hc - 1});
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
