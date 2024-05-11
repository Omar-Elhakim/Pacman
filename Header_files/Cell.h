#ifndef CELL_H
#define CELL_H
#include <raylib.h>

typedef enum { ROAD, WALL } TileType_t;



struct Cell {
    Rectangle rec;
    TileType_t TileType;
    Color BackgroundColor;
    Vector2 arrPos;
    bool hasFood;
    void Draw() {
        DrawRectangleRec(rec, BackgroundColor);
    }
};

#endif // CELL_H
