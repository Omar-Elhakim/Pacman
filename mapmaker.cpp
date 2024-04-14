#include "mapmaker.h"
#include "raylib.h"
#include <string>
#include <queue>
#include <vector>
// number of vertical and horizontal cells

float  WindowWidth = 800, WindowHeight = 600;
float  CellWidth = 0, CellHeight = 0;
Cell **CellList = NULL;
Color  pathColor = GREEN;

    const int vc = 40 / 2;
    const int hc = 30 / 2;


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
    // TODO check if the conversion is true
    CellList = new Cell *[hc * sizeof(Cell *)];
    CellWidth = WindowWidth / vc;
    CellHeight = WindowHeight / hc;
    for (int i = 0; i < hc; i++) {
        // TODO check if the conversion is true
        CellList[i] = new Cell [vc * sizeof(Cell)];
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


bool isPath(int x, int y) {
    if (y >= hc || x >= vc || y < 0 || x < 0)
        return false;
    if (CellList[y][x].TileType == WALL)
        return false;
    return true;
}


void BFS(Vector2i prev[vc][hc], Vector2i from){
    int row = 0, col = 0;
    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};
    queue<Vector2i> TN;
    TN.push(from);
    bool visited[hc][vc];
    for (int i = 0; i < hc; i++)
        for (int j = 0; j < vc; j++)
            visited[i][j] = false;

    while (!TN.empty()) {
        Vector2i s=TN.front();
        for (int i = 0; i < 4; i++) {
            col = s.x + dc[i];
            row = s.y + dr[i];
            if (isPath(col, row) && !visited[row][col]) {
                visited[row][col] = true;
                prev[row][col] = s;
                TN.push(prev[row][col]);
            }
        }
    TN.pop();
    }
}



void findPath(Vector2i from, Vector2i to) {
    vector<Vector2i> Path;
    Vector2i prev[vc][hc];
    prev[0][0].x=prev[0][0].y=-1;
    BFS(prev, from);
    Vector2i temp = to;
    int   row = 0, col = 0;
    do {
        row = temp.y;
        col = temp.x;
        if ((.x==0 && prev[row][col].y==0 && )) {
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