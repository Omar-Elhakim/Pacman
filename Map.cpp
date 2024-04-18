#include "Map.h"
#include <raylib.h>

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

void Map::makeList() {
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

void Map::draw() {
    for (int i = 0; i < hc; i++) {
        for (int j = 0; j < vc; j++) {
            getCell(i, j)->Draw();
        }
    }
}

Cell *Map::getCell(int row, int col) {
    if (col < vc && row < hc && col >= 0 && row >= 0) {
        return &list[row][col];
    } else
        return nullptr;
}

Map::Map() {
    makeList();
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
