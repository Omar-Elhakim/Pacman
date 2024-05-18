#include "../Header_files/Ghost.h"
#include "../Header_files/Level.h"
#include "../Header_files/Map.h"
#include "../Header_files/pacman.h"
#include <random>
#include <raylib.h>
using namespace std;

Ghost::Ghost(Map *map, float speed) : map(map), speed(speed) {

    ghostImages[0] = LoadImage("assets/cyanGhost.png");
    ghostImages[1] = LoadImage("assets/redGhost.png");
    ghostImages[2] = LoadImage("assets/orangeGhost.png");
    ghostImages[3] = LoadImage("assets/pinkGhost.png");
    imageSize = {0, 0};
    a = 0;
    x = 0;
    imageSize = {2 * map->CellWidth, 2 * map->CellHeight};
    setSize();
    for (int i = 0; i < 4; i++)
        InitialPosition[i] = map->getClPos(GetRandomCl(map));
    Direction = {0, 0};
}

Ghost::~Ghost() {
    for (int i = 0; i < 4; i++)
        UnloadTexture(ghostText[i]);
}
void Ghost::setSize() {
    Vector2 OldImageSize = imageSize;
    imageSize = {2 * map->CellWidth, 4 * map->CellHeight};
    speed *= (imageSize.x * imageSize.y) / (OldImageSize.x * OldImageSize.y);

    for (size_t i = 0; i < 4; i++) {
        ImageResize(&ghostImages[i], imageSize.x, imageSize.y);
        ghostText[i] = LoadTextureFromImage(ghostImages[i]);
        ghostbox[i] = {0, 0, ghostImages[i].width / 2.f, ghostText[i].height / 4.f};
        UnloadImage(ghostImages[i]);
    }
}

void Ghost::draw() {

    for (size_t i = 0; i < 4; i++) {
        DrawTextureRec(ghostText[i], ghostbox[i], InitialPosition[i], WHITE);
    }
}

void Ghost::move(int i) {
    // for (int i = 0; i < 4; i++)
    // {
    a++;
    if (a % 9 == 0) x = (x + 1) % 3;
    ghostbox[i].x = x * ghostbox[i].width;
    InitialPosition[i].x += Direction.x;
    InitialPosition[i].y += Direction.y;
    // }
}

void Ghost::goRight(int i) {
    Vector2 pointerTL = {InitialPosition[i].x + 1, InitialPosition[i].y + 2};
    Vector2 pointerBR = {InitialPosition[i].x + map->CellWidth - 1, InitialPosition[i].y + map->CellHeight - 2};
    Direction = {speed, 0};
    ghostbox[i].y = 0 * ghostbox[i].height;
    if ((map->GetCell({(int)((pointerTL.x / map->CellWidth) + 1),
                       (int)((pointerTL.y - map->infoBarHeight) / map->CellHeight)})
             ->TileType == ROAD) &&
        (map->GetCell({(int)((pointerBR.x / map->CellWidth) + 0.01f),
                       (int)((pointerBR.y - map->infoBarHeight) / map->CellHeight)})
             ->TileType == ROAD)) {
        move(i);
    }
}

void Ghost::goLeft(int i) {
    Vector2 pointerTL = {InitialPosition[i].x + 1, InitialPosition[i].y + 2};
    Vector2 pointerBR = {InitialPosition[i].x + map->CellWidth - 1, InitialPosition[i].y + map->CellHeight - 2};
    Direction = {-1 * speed, 0};
    ghostbox[i].y = 1 * ghostbox[i].height;
    if ((map->GetCell({(int)((pointerTL.x / map->CellWidth) - 0.01f),
                       (int)((pointerTL.y - map->infoBarHeight) / map->CellHeight)})
             ->TileType == ROAD) &&
        (map->GetCell({(int)((pointerBR.x / map->CellWidth) - 1),
                       (int)((pointerBR.y - map->infoBarHeight) / map->CellHeight)})
             ->TileType == ROAD)) {
        move(i);
    }
}

void Ghost::goUp(int i) {
    Vector2 pointerTL = {InitialPosition[i].x + 1, InitialPosition[i].y + 2};
    Vector2 pointerBR = {InitialPosition[i].x + map->CellWidth - 1, InitialPosition[i].y + map->CellHeight - 2};
    Direction = {0, -1 * speed};
    ghostbox[i].y = 2 * ghostbox[i].height;
    if ((map->GetCell({(int)(pointerTL.x / map->CellWidth),
                       (int)(((pointerTL.y - map->infoBarHeight) / map->CellHeight) - 0.01f)})
             ->TileType == ROAD) &&
        (map->GetCell({(int)(pointerBR.x / map->CellWidth),
                       (int)(((pointerBR.y - map->infoBarHeight) / map->CellHeight) - 1)})
             ->TileType == ROAD)) {
        move(i);
    }
}

void Ghost::goDown(int i) {
    Vector2 pointerTL = {InitialPosition[i].x + 1, InitialPosition[i].y + 2};
    Vector2 pointerBR = {InitialPosition[i].x + map->CellWidth - 1, InitialPosition[i].y + map->CellHeight - 2};
    Direction = {0, speed};
    ghostbox[i].y = 3 * ghostbox[i].height;
    if ((map->GetCell({(int)(pointerTL.x / map->CellWidth),
                       (int)(((pointerTL.y - map->infoBarHeight) / map->CellHeight) + 1)})
             ->TileType == ROAD) &&
        (map->GetCell({(int)(pointerBR.x / map->CellWidth),
                       (int)(((pointerBR.y - map->infoBarHeight) / map->CellHeight) + 0.01f)})
             ->TileType == ROAD)) {
        move(i);
    }
}

Vector2 Ghost::GenerateRandomDirection() {
    Vector2 dir;
    dir.x = GetRandomValue(-1, 1);
    dir.y = GetRandomValue(-1, 1);
    float length = sqrtf(dir.x * dir.x + dir.y * dir.y);
    // Avoid division by zero
    if (length > 0) {
        dir.x /= length;
        dir.y /= length;
    }
    return dir;
}

void Ghost::moveRandomly(float speed) {
    if (GetRandomValue(0, 100) < 5) {
        Vector2 direction = GenerateRandomDirection();
        Vector2 velocity = {direction.x * speed, direction.y * speed};
        InitialPosition[0].x += velocity.x;
        InitialPosition[0].y += velocity.y;
    }
}

void Ghost::moveto(Vector2 to, int ghostindex, Map *map) {
    vector<Vector2i> path = map->FindPath(map->getClArrPos(InitialPosition[ghostindex]), map->getClArrPos(to));
    cout << path[0].x;
    Vector2 relativePos;
    relativePos.x = InitialPosition[ghostindex].x - path[0].x;
    relativePos.y = InitialPosition[ghostindex].y - path[0].y;
    if (relativePos.x == 0) { // it's in the same column, let's see the difference in rows
        if (relativePos.y == 1)
            goUp(ghostindex); // it's on top of it
        else if (relativePos.y == -1)
            goDown(ghostindex);
    } else {
        if (relativePos.x == 1)
            goLeft(ghostindex); // it's in the same column, let's see the difference in rows
        else if (relativePos.x == -1)
            goRight(ghostindex); // it's in the same column, let's see the difference in rows
    }
    cout << "function ended";
}
