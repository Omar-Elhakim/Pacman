#include "include/mapmaker.h"
#include <raylib.h>
#include <stdio.h>
#include <string.h>

const int numTiles = 10;
float     WindowWidth = 800;
float     SquareWidth = 0;
Square  **SquareList = NULL;
Color     pathColor = GREEN;

int main() {
    InitSquares();
    game();
    destroySquareList();
    return 0;
}

void _PrintSq(void *SqAddr) { ((Square *)(*((size_t *)SqAddr)))->BackgroundColor = pathColor; }

bool _QSearchSq(node_t *node, void *data) { return *((size_t *)node_data(node)) == (size_t)data; }

void ColorSqList() {
    for (int i = 0; i < numTiles; i++) {
        for (int j = 0; j < numTiles; j++) {
            if (isEven(i + j)) {
                SquareList[i][j].BackgroundColor = BROWN;
            } else
                SquareList[i][j].BackgroundColor = WHITE;
        }
    }
}

void InitSquares() {
    SquareList = (Square **)malloc(numTiles * sizeof(Square *));
    SquareWidth = WindowWidth / numTiles;
    for (int i = 0; i < numTiles; i++) {
        SquareList[i] = (Square *)malloc(numTiles * sizeof(Square));
        for (int j = 0; j < numTiles; j++) {
            SquareList[i][j].TileType = PATH;
            SquareList[i][j].obj = NULL;
            SquareList[i][j].pos.x = j;
            SquareList[i][j].pos.y = i;
            SquareList[i][j].rec.x = j * SquareWidth;
            SquareList[i][j].rec.y = i * SquareWidth;
            SquareList[i][j].rec.width = SquareList[i][j].rec.height = SquareWidth;
        }
    }
    ColorSqList();
}

// just takes square address
void AllocateSqP(node_t *node, void *data) {
    size_t *temp = malloc(sizeof(size_t));
    *temp = (size_t)data;
    node_set_data(node, temp);
}

bool isPath(int x, int y) {
    if (y >= numTiles || x >= numTiles || y < 0 || x < 0)
        return false;
    if (SquareList[y][x].TileType == WALL)
        return false;
    return true;
}

void InsertNeighbors(gqueue_t *queue, Square ***prev, Square *from) {
    int row = 0, col = 0;
    int dr[4] = {0, 0, -1, 1};
    int dl[4] = {-1, 1, 0, 0};

    gqueue_t *TN = create_queue(AllocateSqP);
    enqueue(TN, from);
    bool visited[numTiles][numTiles];
    for (int i = 0; i < numTiles; i++)
        for (int j = 0; j < numTiles; j++)
            visited[i][j] = false;

    while (!queue_is_empty(TN)) {
        Square *s = ((Square *)*(size_t *)queue_front(TN));
        for (int i = 0; i < 4; i++) {
            col = s->pos.x + dl[i];
            row = s->pos.y + dr[i];
            if (isPath(col, row) && !visited[row][col]) {
                visited[row][col] = true;
                prev[row][col] = s;
                enqueue(queue, &SquareList[row][col]);
                enqueue(TN, &SquareList[row][col]);
            }
        }
        dequeue(TN);
    }

    destroy_queue(&TN);
}

void findPath(Square *from, Square *to) {
    linked_list_t *Path = create_list(AllocateSqP);
    gqueue_t      *Neighbors = create_queue(AllocateSqP);
    Square      ***prev = (Square ***)malloc(numTiles * sizeof(Square **));
    for (int i = 0; i < numTiles; i++) {
        prev[i] = (Square **)malloc(numTiles * sizeof(Square *));
        for (int j = 0; j < numTiles; j++) {
            prev[i][j] = NULL;
        }
    }

    InsertNeighbors(Neighbors, prev, from);
    Square *temp = to;
    int     row = 0, col = 0;
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
    for (int i = 0; i < numTiles; i++) {
        free(prev[i]);
    }
    free(prev);
}

void destroySquareList() {
    for (int i = 0; i < numTiles; i++) {
        free(SquareList[i]);
    }
    free(SquareList);
}

void makePath(int x, int y) {
    SquareList[y][x].TileType = WALL;
    SquareList[y][x].BackgroundColor = BLACK;
}

bool MouseInBoundries(Vector2 MousePos) {
    if (MousePos.x < WindowWidth && MousePos.y < WindowWidth && MousePos.y > 0 && MousePos.x > 0) {
        return true;
    } else
        return false;
}

int game() {
    SetTraceLogLevel(LOG_NONE);
    InitWindow(WindowWidth, WindowWidth, "mapmaker");
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);
        for (int i = 0; i < numTiles; i++) {
            for (int j = 0; j < numTiles; j++) {
                DrawRectangleRec(SquareList[i][j].rec, SquareList[i][j].BackgroundColor);
            }
        }
        if (IsKeyPressed(KEY_Q)) {
            break;
        }
        if (IsKeyPressed(KEY_R)) {
            ColorSqList();
            for (int i = 0; i < numTiles; i++) {
                for (int j = 0; j < numTiles; j++) {
                    SquareList[i][j].TileType = PATH;
                }
            }
        }
        if (IsKeyPressed(KEY_F)) {
            findPath(&SquareList[0][0], &SquareList[numTiles - 1][numTiles - 1]);
        }
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && MouseInBoundries(GetMousePosition())) {
            makePath((int)(GetMouseX() / SquareWidth), (int)(GetMouseY() / SquareWidth));
        }
        EndDrawing();
    }
    CloseWindow();
    return EXIT_SUCCESS;
}
