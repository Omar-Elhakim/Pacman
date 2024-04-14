#pragma once
#include <raylib.h>

typedef enum { PATH, WALL } TileType_t;

struct Vector2i {
    int x, y;
};

struct Cell {
    Rectangle rec;
    TileType_t TileType;
    Color BackgroundColor;
    Vector2i pos;
    void Draw() {
        DrawRectangleRec(rec, BackgroundColor);
    }
};
