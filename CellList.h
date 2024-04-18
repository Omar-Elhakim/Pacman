#include "Cell.h"
#include <vector>

#define isEven(x) ((x) % 2 == 0 ? true : false)

const int vc = 40 / 2;
const int hc = 30 / 2;

class CellList {
    
  public:
    void makeList();
    void SetCellsSize();
    void SetCellsPos();
    Color pathColor = GREEN;
    Cell** list;
    float CellWidth, CellHeight;
    void ColorClList();
    void ColorClSubList(std::vector<Vector2i> list);
    void SetPathColor(Color color);
    void Update();
    Cell *getCell(int row, int col);
    CellList();
    ~CellList();
};
