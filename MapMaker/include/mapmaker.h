#include "gqueue.h"
#include "gstack.h"
#include <raylib.h>
#include <stdlib.h>

#define isEven(x) ((x) % 2 == 0 ? true : false)

typedef enum { PATH, WALL } TileType_t;

typedef struct Vector2i {
    int x, y;
} Vector2i;

typedef struct Square {
    Rectangle  rec;
    Rectangle *obj;
    TileType_t TileType;
    Color      BackgroundColor;
    Vector2i   pos;
} Square;

void _PrintSq(void *addr);
bool _QSearchSq(node_t *node, void *data);
void ColorSqList();
void InitSquares();
void AllocateSqP(node_t *node, void *data);
void InsertNeighbors(gqueue_t *queue, Square ***prev, Square *from);
void findPath(Square *from, Square *to);
void destroySquareList();
int  game();
