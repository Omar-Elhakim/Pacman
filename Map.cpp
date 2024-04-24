#include "Map.h"
#include <queue>
#include <raylib.h>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

Map::Map() {
    MakeList();
    SetCellsSize();
    SetCellsPos();
    for (int i = 0; i < hc; i++) {
        for (int j = 0; j < vc; j++) {
            list[i][j].TileType = ROAD;
            list[i][j].pos.x = j;
            list[i][j].pos.y = i;
            if (isEven(i + j)) {
                list[i][j].BackgroundColor = BROWN;
            } else
                list[i][j].BackgroundColor = WHITE;
        }
    }
}

Map::~Map() {
    for (int i = 0; i < hc; i++) {
        delete[] list[i];
        list[i] = nullptr;
    }
    delete[] list;
}

bool Map::isPath(int x, int y) {
    if (y >= hc || x >= vc || y < 0 || x < 0)
        return false;
    if (GetCell(y, x)->TileType == WALL)
        return false;
    return true;
}

void Map::BFS(Vector2i prev[][vc], Vector2i from) {
    int row = from.y, col = from.x;
    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};
    std::queue<Vector2i> TN;
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
            GetCell(s.y, s.x)->BackgroundColor = GREEN;
            if (isPath(col, row) && !visited[row][col]) {
                visited[row][col] = true;
                prev[row][col] = s;
                TN.push({col, row});
            }
        }
        TN.pop();
    }
}

void Map::SetCellsSize() {
    CellWidth = static_cast<float>(GetScreenWidth()) / vc;
    CellHeight = static_cast<float>(GetScreenHeight()) / hc;
    for (int i = 0; i < hc; i++) {
        for (int j = 0; j < vc; j++) {
            list[i][j].rec.width = CellWidth;
            list[i][j].rec.height = CellHeight;
        }
    }
}

void Map::SetCellsPos() {
    CellWidth = static_cast<float>(GetScreenWidth()) / vc;
    CellHeight = static_cast<float>(GetScreenHeight()) / hc;
    for (int i = 0; i < hc; i++) {
        for (int j = 0; j < vc; j++) {
            list[i][j].rec.x = j * CellWidth;
            list[i][j].rec.y = i * CellHeight;
        }
    }
}

void Map::ColorClList() {
    for (int i = 0; i < hc; i++) {
        for (int j = 0; j < vc; j++) {
            if (list[i][j].TileType == WALL)
                continue;
            if (isEven(i + j)) {
                list[i][j].BackgroundColor = BROWN;
            } else
                list[i][j].BackgroundColor = WHITE;
        }
    }
}

void Map::MakeList() {
    list = new Cell *[hc];
    for (int i = 0; i < hc; i++)
        list[i] = new Cell[vc];
}

void Map::SetPathColor(Color color) {
    pathColor = color;
}

void Map::ColorClSubList(std::vector<Vector2i> subList) {
    for (int i = 0; i < subList.size(); i++)
        list[subList[i].y][subList[i].x].BackgroundColor = pathColor;
}

void Map::Update() {
    SetCellsSize();
    SetCellsPos();
}

void Map::Draw() {
    for (int i = 0; i < hc; i++) {
        for (int j = 0; j < vc; j++) {
            GetCell(i, j)->Draw();
        }
    }
}

void Map::FindPath(Vector2i from, Vector2i to) {
    std::vector<Vector2i> Path;
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

    SetPathColor(RED);
    ColorClSubList(Path);
    GetCell(to.y, to.x)->BackgroundColor = GOLD;
    SetPathColor(GREEN);
}

Cell *Map::GetCell(int row, int col) {
    if (col < vc && row < hc && col >= 0 && row >= 0) {
        return &list[row][col];
    } else
        return nullptr;
}



string Map::toString(){
   int height = 15;
   int width = 20;
   Cell** list{};
   stringstream ss;
   ss << height << " " << width;
   MakeList();
   SetCellsSize();
   SetCellsPos();
   for (int i = 0; i < hc; i++) {
       for (int j = 0; j < vc; j++) {
           list[i][j].TileType = ROAD;
           list[i][j].pos.x = j;
           list[i][j].pos.y = i;
           if (isEven(i + j)) {
               list[i][j].BackgroundColor = BROWN;
           }
           else
               list[i][j].BackgroundColor = WHITE;
       }
   }
    return ss.str();

}