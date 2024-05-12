#include "../Header_files/Map.h"

Map::Map() {
    MakeList();
    SetCellsSize();
    SetCellsPos();
    for (int i = 0; i < hc; i++) {
        for (int j = 0; j < vc; j++) {
            list[i][j].TileType = ROAD;
            list[i][j].arrPos.x = j;
            list[i][j].arrPos.y = i;
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
    if (y >= hc || x >= vc || y < 0 || x < 0) return false;
    if (GetCell(x, y)->TileType == WALL) return false;
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
            if(colorPath) GetCell(s.x, s.y)->BackgroundColor = GREEN;
            if (isPath(col, row) && !visited[row][col]) {
                visited[row][col] = true;
                prev[row][col] = s;
                Vector2i k = {col, row};
                TN.push(k);
            }
        }
        TN.pop();
    }
}

void Map::SetCellsSize() {
    CellWidth = static_cast<float>(GetScreenWidth()) / vc;
    CellHeight = static_cast<float>(GetScreenHeight() - infoBarHeight) / (hc);
    for (int i = 0; i < hc; i++) {
        for (int j = 0; j < vc; j++) {
            list[i][j].rec.width = CellWidth;
            list[i][j].rec.height = CellHeight;
        }
    }
}

void Map::SetCellsPos() {
    for (int i = 0; i < hc; i++) {
        for (int j = 0; j < vc; j++) {
            list[i][j].rec.x = j * CellWidth;
            list[i][j].rec.y = i * CellHeight + infoBarHeight;
        }
    }
}

void Map::ColorClList() {
    for (int i = 0; i < hc; i++) {
        for (int j = 0; j < vc; j++) {
            if (list[i][j].TileType == WALL) continue;
            if (isEven(i + j)) {
                list[i][j].BackgroundColor = BROWN;
            } else
                list[i][j].BackgroundColor = WHITE;
        }
    }
}

void Map::ColorMap() {
    for (int i = 0; i < hc; i++) {
        for (int j = 0; j < vc; j++) {
            list[i][j].BackgroundColor = (list[i][j].TileType == WALL) ? BLUE : BLACK;
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
            GetCell(j, i)->Draw();
        }
    }
}

#include <iostream>
vector<Vector2i> Map::FindPath(Vector2i from, Vector2i to) {
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
    if (colorPath) {
        SetPathColor(RED);
        ColorClSubList(Path);
        GetCell(to.x, to.y)->BackgroundColor = GOLD;
        SetPathColor(GREEN);
    }
    return Path;
}

Cell *Map::GetCell(int col, int row) {
    if (col < vc && row < hc && col >= 0 && row >= 0) {
        return &list[row][col];
    } else
        return nullptr;
}

bool Map::posInGameCanvas(Vector2 Position) {
    return posInBoundaries(Position) && Position.y > infoBarHeight;
}

bool Map::posInInfoBar(Vector2 Position) {
    return posInBoundaries(Position) && Position.y <= infoBarHeight;
}

bool Map::posInBoundaries(Vector2 Position) {
    return Position.x < GetScreenWidth() && Position.y < GetScreenHeight() && Position.x > 0 && Position.y > 0;
}

Vector2i Map::getClArrPos(Vector2 Position) {
    if (posInGameCanvas(Position)) return {(int)(Position.x / CellWidth), ((int)((Position.y - infoBarHeight) / CellHeight))};
    return {-1, -1};
}

Vector2 Map::getClPos(Vector2i ArrPos) {
    if (ArrPos.x < vc && ArrPos.y < hc && ArrPos.x >= 0 && ArrPos.y >= 0)
        return {ArrPos.x * CellWidth, ArrPos.y * CellHeight + infoBarHeight};
    return {-1, -1};
}
