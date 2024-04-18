#ifndef CELLLIST_H
#define CELLLIST_H
#include "Cell.h"
#include <vector>

#define isEven(x) ((x) % 2 == 0 ? true : false)

const int vc = 40 / 2;
const int hc = 30 / 2;

class Map {

  public:
    Color pathColor = GREEN;
    Cell **list;
    float CellWidth, CellHeight;
    void makeList();
    void SetCellsSize();
    void SetCellsPos();
    void ColorClList();
    void ColorClSubList(std::vector<Vector2i> list);
    void SetPathColor(Color color);
    void Update();
    void draw();
    Cell *getCell(int row, int col);
    Map();
    ~Map();
};

#endif // CELLLIST_H
