#include "gqueue.h"
#include "gstack.h"
#include <raylib.h>
#include <stdlib.h>

#define isEven(x) ((x) % 2 == 0 ? true : false)

typedef enum { PATH, WALL } TileType_t;

typedef struct Vector2i {
    int x, y;
} Vector2i;

typedef struct Cell {
    Rectangle  rec;
    Rectangle *obj;
    TileType_t TileType;
    Color      BackgroundColor;
    Vector2i   pos;
} Cell;

int  game();
void ColorClList();
void InitCells();
void BFS(gqueue_t *queue, Cell ***prev, Cell *from);
void findPath(Cell *from, Cell *to);
void makeWall(int x, int y);
void makePath(int x, int y);
void destroyCellList();
void _AllocateCl(node_t *node, void *data);
void _PrintCl(void *addr);
bool _QSearchCl(node_t *node, void *data);
