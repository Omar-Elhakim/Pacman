#include "include/mapmaker.h"
#include <raylib.h>
#include <stdio.h>
#include <string.h>

// number of vertical and horizontal cells
const int vc = 40 / 2;
const int hc = 30 / 2;

float  WindowWidth = 800, WindowHeight = 600;
float  CellWidth = 0, CellHeight = 0;
Cell **CellList = NULL;
Color  pathColor = GREEN;

int main() {
    InitCells();
    game();
    destroyCellList();
    return 0;
}

void _PrintSq(void *SqAddr) { ((Cell *)(*((size_t *)SqAddr)))->BackgroundColor = pathColor; }

bool _QSearchSq(node_t *node, void *data) { return *((size_t *)node_data(node)) == (size_t)data; }

void ColorSqList() {
    for (int i = 0; i < hc; i++) {
        for (int j = 0; j < vc; j++) {
            if (isEven(i + j)) {
                CellList[i][j].BackgroundColor = BROWN;
            } else
                CellList[i][j].BackgroundColor = WHITE;
        }
    }
}

void InitCells() {
    CellList = (Cell **)malloc(hc * sizeof(Cell *));
    CellWidth = WindowWidth / vc;
    CellHeight = WindowHeight / hc;
    for (int i = 0; i < hc; i++) {
        CellList[i] = (Cell *)malloc(vc * sizeof(Cell));
        for (int j = 0; j < vc; j++) {
            CellList[i][j].TileType = PATH;
            CellList[i][j].obj = NULL;
            CellList[i][j].pos.x = j;
            CellList[i][j].pos.y = i;
            CellList[i][j].rec.x = j * CellWidth;
            CellList[i][j].rec.y = i * CellHeight;
            CellList[i][j].rec.width = CellWidth;
            CellList[i][j].rec.height = CellHeight;
        }
    }
    ColorSqList();
}

// just takes square address
void AllocateSqP(node_t *node, void *data) {
    size_t *temp = (size_t *)malloc(sizeof(size_t));
    *temp = (size_t)data;
    node_set_data(node, temp);
}

bool isPath(int x, int y) {
    if (y >= hc || x >= vc || y < 0 || x < 0)
        return false;
    if (CellList[y][x].TileType == WALL)
        return false;
    return true;
}

void BFS(gqueue_t *queue, Cell ***prev, Cell *from) {
    int row = 0, col = 0;
    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};

    gqueue_t *TN = create_queue(AllocateSqP);
    enqueue(TN, from);
    bool visited[hc][vc];
    for (int i = 0; i < hc; i++)
        for (int j = 0; j < vc; j++)
            visited[i][j] = false;

    while (!queue_is_empty(TN)) {
        Cell *s = ((Cell *)*(size_t *)queue_front(TN));
        for (int i = 0; i < 4; i++) {
            col = s->pos.x + dc[i];
            row = s->pos.y + dr[i];
            if (isPath(col, row) && !visited[row][col]) {
                visited[row][col] = true;
                prev[row][col] = s;
                enqueue(queue, &CellList[row][col]);
                enqueue(TN, &CellList[row][col]);
            }
        }
        dequeue(TN);
    }

    destroy_queue(&TN);
}

void findPath(Cell *from, Cell *to) {
    linked_list_t *Path = create_list(AllocateSqP);
    gqueue_t      *Neighbors = create_queue(AllocateSqP);
    Cell        ***prev = (Cell ***)malloc(hc * sizeof(Cell **));
    for (int i = 0; i < hc; i++) {
        prev[i] = (Cell **)malloc(vc * sizeof(Cell *));
        for (int j = 0; j < vc; j++) {
            prev[i][j] = NULL;
        }
    }

    BFS(Neighbors, prev, from);
    Cell *temp = to;
    int   row = 0, col = 0;
    do {
        row = temp->pos.y;
        col = temp->pos.x;
        if (prev[row][col] != NULL) {
            push_front(Path, temp);
        } else {
            break;
        }
        temp = prev[row][col];
    } while (temp != from);
    push_front(Path, from);

    dump_list(queue_list(Neighbors), _PrintSq);
    pathColor = RED;
    dump_list(Path, _PrintSq);
    pathColor = GREEN;

    destroy_queue(&Neighbors);
    destroy_list(&Path);
    for (int i = 0; i < hc; i++) {
        free(prev[i]);
    }
    free(prev);
}

void destroyCellList() {
    for (int i = 0; i < hc; i++) {
        free(CellList[i]);
    }
    free(CellList);
}

void makeWall(int x, int y) {
    CellList[y][x].TileType = WALL;
    CellList[y][x].BackgroundColor = BLACK;
}

void makePath(int x, int y) {
    CellList[y][x].TileType = PATH;
    Color temp = BLACK;
    if (isEven(x + y)) {
        temp = BROWN;
    } else
        temp = WHITE;
    CellList[y][x].BackgroundColor = temp;
}

bool MouseInBoundries(Vector2 MousePos) {
    if (MousePos.x < WindowWidth && MousePos.y < WindowWidth && MousePos.y > 0 && MousePos.x > 0) {
        return true;
    } else
        return false;
}

int game() {
    SetTraceLogLevel(LOG_NONE);
    InitWindow(WindowWidth, WindowHeight, "mapmaker");
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);
        for (int i = 0; i < hc; i++) {
            for (int j = 0; j < vc; j++) {
                DrawRectangleRec(CellList[i][j].rec, CellList[i][j].BackgroundColor);
            }
        }
        if (IsKeyPressed(KEY_Q)) {
            break;
        }
        if (IsKeyPressed(KEY_R)) {
            ColorSqList();
            for (int i = 0; i < hc; i++) {
                for (int j = 0; j < vc; j++) {
                    CellList[i][j].TileType = PATH;
                }
            }
        }
        if (IsKeyPressed(KEY_F)) {
            findPath(&CellList[0][0], &CellList[hc - 1][vc - 1]);
        }
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && MouseInBoundries(GetMousePosition())) {
            makeWall((int)(GetMouseX() / CellWidth), (int)(GetMouseY() / CellHeight));
        }
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT) && MouseInBoundries(GetMousePosition())) {
            makePath((int)(GetMouseX() / CellWidth), (int)(GetMouseY() / CellHeight));
        }
        EndDrawing();
    }
    CloseWindow();
    return EXIT_SUCCESS;
}
