#include "mapmaker.h"
#include "raylib.h"
#include <queue>
#include <vector>
#include <stdio.h>
// number of vertical and horizontal cells

float  WindowWidth = 800, WindowHeight = 600;
float  CellWidth = 0, CellHeight = 0;
Cell **CellList = NULL;
Color  pathColor = GREEN;

int main(){
    InitCells();
    game();
    return 0;
}

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
    CellList = new Cell *[hc ];
    CellWidth = WindowWidth / vc;
    CellHeight = WindowHeight / hc;
    for (int i = 0; i < hc; i++) {
        // TODO check if the conversion is true
        CellList[i] = new Cell [vc ];
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


bool isPath(int x , int y) {
    if (y >= hc || x >= vc || y < 0 || x < 0)
        return false;
    if (CellList[y][x].TileType == WALL)
        return false;
    return true;
}

void ColorVectorList(vector<Vector2i> list){
    for(int i = 0 ; i < list.size();i++)
        CellList[list[i].y][list[i].x].BackgroundColor = pathColor;
}

void BFS(Vector2i prev[hc][vc], Vector2i from){
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
                /*
                if(s.x != 0 &&s.y != 0 ){
                    prev[row][col] = s;
                }else
                    prev[row][col] ={-1,-1};
*/
                TN.push(prev[row][col]);
            }
        }
    TN.pop();
    }
    for(int i = 0 ; i< hc ;i++)
        for(int j = 0 ; j< hc ;j++)
            printf("%d %d - %d %d \n",i,j,prev[i][j].x,prev[i][j].y);
}

void findPath(Vector2i from, Vector2i to) {
    vector<Vector2i> Path;
    Vector2i prev[hc][vc];
    for (int i = 0; i < hc; i++)
        for (int j = 0; j < vc; j++)
            prev[i][j] = {-1,-1};

    BFS(prev, from);
    Vector2i temp = to;
    int   row = temp.y, col = temp.x;

    // for(int i = 0 ; i< hc ;i++)
    //     for(int j = 0 ; j< hc ;j++)
    //         printf("%d %d - %d %d \n",i,j,prev[i][j].x,prev[i][j].y);

    while(prev[row][col].x != -1){
        row = temp.y;
        col = temp.x;
        Path.push_back(temp);
        temp = prev[row][col];
    }

    pathColor = RED;
    ColorVectorList(Path);
    pathColor = GREEN;
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

void game() {
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
            findPath({0,0}, {vc -1,hc -1});
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
    
}
