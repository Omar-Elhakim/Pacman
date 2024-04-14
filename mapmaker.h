#pragma once
#include "raylib.h"

#define isEven(x) ((x) % 2 == 0 ? true : false)

using namespace std;
typedef enum { PATH, WALL } TileType_t;

struct Vector2i {
    int x, y;
} ;

struct Cell {
    Rectangle  rec;
    Rectangle *obj;
    TileType_t TileType;
    Color      BackgroundColor;
    Vector2i   pos;
};

class mapmaker {
public:
    static const int vc = 40 / 2;
    static const int hc = 30 / 2;
    mapmaker();
    Cell cell;
    void ColorSqList();
    void InitCells();
    void BFS(Vector2i prev[vc][hc], Vector2i from);
    void findPath(Vector2i from , Vector2i to);
    void destroyCellList();
    void makeWall(int x, int y);
    void makePath(int x, int y);
    int  game();
    ~mapmaker();
};

const int vc = 40 / 2;
const int hc = 30 / 2;

void ColorSqList();
void InitCells();
void BFS(Vector2i prev[hc][vc], Vector2i from);
void findPath(Vector2i from , Vector2i to);
void destroyCellList();
void makeWall(int x, int y);
void makePath(int x, int y);
void game();
