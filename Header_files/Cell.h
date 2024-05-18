#ifndef CELL_H
#define CELL_H
#include <raylib.h>

typedef enum { ROAD, WALL } TileType_t;

typedef struct {
    int x, y;
} Vector2i;

struct Cell {
    Rectangle rec;
    TileType_t TileType;
    Color BackgroundColor;
    Vector2i arrPos;
    bool hasFood;
    void Draw() {
        DrawRectangleRec(rec, BackgroundColor);
    };
    Vector2 getCenter() {
        return {
            rec.x + (rec.width / 2),
            rec.y + (rec.height / 2),
        };
    };
};

#endif // CELL_H
