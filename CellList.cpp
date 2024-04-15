#include "CellList.h"
#include <raylib.h>

void CellList::SetCellsSize() {
    CellWidth = static_cast<float>(GetScreenWidth()) / vc;
    CellHeight = static_cast<float>(GetScreenHeight()) / hc;
    for (int i = 0; i < hc; i++) {
        for (int j = 0; j < vc; j++) {
            list[i][j].rec.width = CellWidth;
            list[i][j].rec.height = CellHeight;
        }
    }
}

void CellList::SetCellsPos() {
    CellWidth = static_cast<float>(GetScreenWidth()) / vc;
    CellHeight = static_cast<float>(GetScreenHeight()) / hc;
    for (int i = 0; i < hc; i++) {
        for (int j = 0; j < vc; j++) {
            list[i][j].rec.x = j * CellWidth;
            list[i][j].rec.y = i * CellHeight;
        }
    }
}

void CellList::ColorClList() {
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

void CellList::makeList() {
    list = new Cell *[hc];
    for (int i = 0; i < hc; i++)
        list[i] = new Cell[vc];
}

void CellList::SetPathColor(Color color) {
    pathColor = color;
}

void CellList::ColorClSubList(std::vector<Vector2i> subList) {
    for (int i = 0; i < subList.size(); i++)
        list[subList[i].y][subList[i].x].BackgroundColor = pathColor;
}

void CellList::Update() {
    SetCellsSize();
    SetCellsPos();
}

Cell *CellList::getCell(int row, int col) {
    if (col < vc && row < hc && col >= 0 && row >= 0) {
        return &list[row][col];
    } else
        return nullptr;
}

CellList::CellList() {
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

CellList::~CellList() {
    for (int i = 0; i < hc; i++) {
        delete[] list[i];
        list[i] = nullptr;
    }
    delete[] list;
}
