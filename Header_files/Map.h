#pragma once
#include "Cell.h"
#include <vector>
#include <string>
#include <queue>
#include <raylib.h>
using namespace std;

#define isEven(x) ((x) % 2 == 0 ? true : false)

const int vc = 40 / 2;
const int hc = 30 / 2;

class Map {
    void BFS(Vector2 prev[][vc], Vector2 from);
    void SetCellsPos();
    void SetCellsSize();
    void MakeList();
    

public:
    Color pathColor = GREEN;
    Cell **list;
    float CellWidth, CellHeight;
    int infoBarHeight = 50;
    void ColorClList();
    void ColorMap();
    void ColorClSubList(vector<Vector2> list);
    void SetPathColor(Color color);
    void Update();
    void Draw();
    void FindPath(Vector2 from, Vector2 to);
    bool posInGameCanvas(Vector2 Pos);
    bool posInInfoBar(Vector2 Pos);
    bool posInBoundaries(Vector2 Pos);
    bool isPath(int x, int y);
    Cell *GetCell(int col, int row);
    Vector2 getClArrPos(Vector2 Position);
    Vector2 getClPos(Vector2 ArrPos);
    Map();
    ~Map();
};
