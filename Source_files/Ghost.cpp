#include <raylib.h>
#include <random>
#include <map>
#include <chrono>
#include <thread>
#include "../Header_files/Map.h"
#include "../Header_files/Ghost.h"
#include "../Header_files/Level.h"
#include "../Header_files/pacman.h"
using namespace std;

Ghost::Ghost(Map* map) :map(map) {
    
    ghostImages[0] = LoadImage("assets/cyanGhost.png");
    ghostImages[1] = LoadImage("assets/redGhost.png");
    ghostImages[2] = LoadImage("assets/orangeGhost.png");
    ghostImages[3] = LoadImage("assets/pinkGhost.png");
    imageSize = { 0, 0 };
    speed = 2.0f;
    a = 0;
    x = 0;
    //map = nullptr;
    imageSize = { 2 * map->CellWidth, 2 * map->CellHeight };
    setSize();
    InitialPosition[0] = map->getClPos(map->GetCell(17, 9)->arrPos);
    InitialPosition[1] = map->getClPos(map->GetCell(17, 10)->arrPos);
    InitialPosition[2] = map->getClPos(map->GetCell(17, 11)->arrPos);
    InitialPosition[3] = map->getClPos(map->GetCell(17, 12)->arrPos);

    Direction = { 0, 0 };

    // UnloadImage(GhostImage);
   // UnloadTexture(ghostText); 
}


void Ghost::setSize() {
    Vector2 OldImageSize = imageSize;
    imageSize = { 2 * map->CellWidth, 4 * map->CellHeight };
    speed *= (imageSize.x * imageSize.y) / (OldImageSize.x * OldImageSize.y);
       
    for (size_t i = 0; i < 4; i++)
    {
        ImageResize(&ghostImages[i], imageSize.x, imageSize.y);
        ghostText[i] = LoadTextureFromImage(ghostImages[i]);
        ghostbox[i] = { 0,0,ghostImages[i].width / 2.f,ghostText[i].height / 4.f };
    }

    //UnloadImage(GhostImage);
}

void Ghost::draw() {

    for (size_t i = 0; i < 4; i++)
    {
        DrawTextureRec(ghostText[i], ghostbox[i], InitialPosition[i], WHITE);
      
    }
}




void Ghost::move() {
    for (int i = 0; i < 4; i++)
    {
        a++;
        if (a % 9 == 0)
            x = (x + 1) % 3;
        ghostbox[i].x = x * ghostbox[i].width;
        InitialPosition[i].x += Direction.x;
        InitialPosition[i].y += Direction.y;
    }
   
}

void Ghost::goRight() {
    for (size_t i = 0; i < 4; i++)
    {
        Vector2 pointerTL = { InitialPosition[i].x + 1,InitialPosition[i].y + 2};
        Vector2 pointerBR = { InitialPosition[i].x + map->CellWidth - 1,InitialPosition[i].y + map->CellHeight - 2};
        Direction = { speed, 0 };
        ghostbox[i].y = 0 * ghostbox[i].height;
        if ((map->GetCell((pointerTL.x / map->CellWidth) + 1, (pointerTL.y - map->infoBarHeight) / map->CellHeight)->TileType == ROAD) &&
            (map->GetCell((pointerBR.x / map->CellWidth) + 0.01, (pointerBR.y - map->infoBarHeight) / map->CellHeight)->TileType == ROAD)) {
            move();
        }
    }
    
}
void Ghost::goLeft() {
    for (size_t i = 0; i < 4; i++) {
        Vector2 pointerTL = { InitialPosition[i].x + 1,InitialPosition[i].y + 2};
        Vector2 pointerBR = { InitialPosition[i].x + map->CellWidth - 1,InitialPosition[i].y + map->CellHeight - 2};
        Direction = { -1 * speed, 0 };
        ghostbox[i].y = 1 * ghostbox[i].height;
        if ((map->GetCell((pointerTL.x / map->CellWidth) - 0.01, (pointerTL.y - map->infoBarHeight) / map->CellHeight)->TileType == ROAD) &&
            (map->GetCell((pointerBR.x / map->CellWidth) - 1, (pointerBR.y - map->infoBarHeight) / map->CellHeight)->TileType == ROAD)) {
            move();
        }
    }
    
}
void Ghost::goUp() {
    for (size_t i = 0; i < 4; i++)
    {
        Vector2 pointerTL = { InitialPosition[i].x + 1,InitialPosition[i].y + 2};
        Vector2 pointerBR = { InitialPosition[i].x + map->CellWidth - 1,InitialPosition[i].y + map->CellHeight - 2};
        Direction = { 0, -1 * speed };
        ghostbox[i].y = 2 * ghostbox[i].height;
        if ((map->GetCell(pointerTL.x / map->CellWidth, ((pointerTL.y - map->infoBarHeight) / map->CellHeight) - 0.01)->TileType == ROAD) &&
            (map->GetCell(pointerBR.x / map->CellWidth, ((pointerBR.y - map->infoBarHeight) / map->CellHeight) - 1)->TileType == ROAD)) {
            move();
        }
    }
    
    
}
void Ghost::goDown() {
    for (size_t i = 0; i < 4; i++)
    {
        Vector2 pointerTL = { InitialPosition[i].x + 1,InitialPosition[i].y + 2};
        Vector2 pointerBR = { InitialPosition[i].x + map->CellWidth - 1,InitialPosition[i].y + map->CellHeight - 2};
        Direction = { 0, speed };
        ghostbox[i].y = 3 * ghostbox[i].height;
        if ((map->GetCell(pointerTL.x / map->CellWidth, ((pointerTL.y - map->infoBarHeight) / map->CellHeight) + 1)->TileType == ROAD) &&
            (map->GetCell(pointerBR.x / map->CellWidth, ((pointerBR.y - map->infoBarHeight) / map->CellHeight) + 0.01)->TileType == ROAD)) {
            move();
        }
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

    
    Vector2 randomDir = GenerateRandomDirection();
    if (GetRandomValue(0, 100) < 5) { 
        Vector2 direction = GenerateRandomDirection();
        Vector2 velocity = { direction.x * speed, direction.y * speed };
        InitialPosition[0].x += velocity.x;
        InitialPosition[0].y += velocity.y;
    }

}



