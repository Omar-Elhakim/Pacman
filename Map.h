#ifndef CELLLIST_H
#define CELLLIST_H
#include "Cell.h"
#include <vector>
#include <string>
using namespace std;

#define isEven(x) ((x) % 2 == 0 ? true : false)

const int vc = 40 / 2;
const int hc = 30 / 2;

class Map {
public:
    void BFS(Vector2i prev[][vc], Vector2i from);
    void SetCellsPos();
    void SetCellsSize();
    void MakeList();
    bool isPath(int x, int y);

  
    Color pathColor = GREEN;
    Cell **list;
    float CellWidth, CellHeight;
    void ColorClList();
    void ColorClSubList(std::vector<Vector2i> list);
    void SetPathColor(Color color);
    void Update();
    void Draw();
    void FindPath(Vector2i from, Vector2i to);
    Cell *GetCell(int row, int col);
    string toString();
    Map();
    ~Map();
};

#endif // CELLLIST_H
