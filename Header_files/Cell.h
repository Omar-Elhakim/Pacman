#ifndef CELL_H
#define CELL_H
#include <raylib.h>

typedef enum { ROAD, WALL } TileType_t;


typedef struct{
    int x,y;
}Vector2i;

struct Cell {
    Rectangle rec;
    TileType_t TileType;
    Color BackgroundColor;
    Vector2i arrPos;
    bool hasFood;
    void Draw() {
        DrawRectangleRec(rec, BackgroundColor);
    }
};

#endif // CELL_H
