#pragma once
#include "Cell.h"
#include <vector>
#include <string>
using namespace std;

#define isEven(x) ((x) % 2 == 0 ? true : false)

const int vc = 40 / 2;
const int hc = 30 / 2;

class Map {
    void BFS(Vector2i prev[][vc], Vector2i from);
    void SetCellsPos();
    void SetCellsSize();
    void MakeList();
    bool isPath(int x, int y);

public:
    Color pathColor = GREEN;
    Cell **list;
    float CellWidth, CellHeight;
    int infoBarHeight = 50;
    void ColorClList();
    void ColorClSubList(std::vector<Vector2i> list);
    void SetPathColor(Color color);
    void Update();
    void Draw();
    void FindPath(Vector2i from, Vector2i to);
    bool posInGameCanvas(Vector2 Pos);
    bool posInInfoBar(Vector2 Pos);
    bool posInBoundaries(Vector2 Pos);
    Cell *GetCell(int col, int row);
    Vector2i getClArrPos(Vector2 Position);
    Vector2 getClPos(Vector2i ArrPos);
    Map();
    ~Map();
};
