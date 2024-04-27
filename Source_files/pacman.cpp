#include "../Header_files/pacman.h"
#include "raylib.h"

#include "../Header_files/Level.h"

Pacman::Pacman(Map *map, Food* food) : map(map),food(food) {
    speed = 1.8f;
    x = 0;
    a = 0;
    ImageSize = {2 * map->CellWidth, 4 * map->CellHeight};
    setSize();
    InitialPosition =  map->getClPos(map->GetCell(1, 1)->arrPos);
    direction = {0, 0};
}

Pacman::Pacman(Map* map) : map(map){
    speed = 1.8f;
    x = 0;
    a = 0;
    ImageSize = { 2 * map->CellWidth, 4 * map->CellHeight };
    setSize();
    InitialPosition = map->getClPos(map->GetCell(0, 0)->arrPos);
    direction = { 0, 0 };
}


Pacman::~Pacman() {
    UnloadTexture(pacmanText);
}

void Pacman::draw() {
    DrawTextureRec(pacmanText, AnimationBox, InitialPosition, WHITE);
}

void Pacman::move() {
    a++;
    if (a % 9 == 0)
        x = (x + 1) % 3;
    AnimationBox.x = x * AnimationBox.width;
    InitialPosition.x += direction.x;
    InitialPosition.y += direction.y;
    
}
void Pacman::eat() {
    Vector2 midpoint = { (InitialPosition.x + (map->CellWidth/2)),(InitialPosition.y + (map->CellHeight/2)) };
    if (map->GetCell(midpoint.x / map->CellWidth, (midpoint.y - map->infoBarHeight) / map->CellHeight)->hasFood == true) {

        map->GetCell(midpoint.x / map->CellWidth, (midpoint.y - map->infoBarHeight) / map->CellHeight)->hasFood = false;
        score1 += 100000000;
    }

}
void Pacman::goRight() {
    Vector2 pointerTL = { InitialPosition.x + 1,InitialPosition.y + 2 };
    Vector2 pointerBR = { InitialPosition.x + map->CellWidth - 1,InitialPosition.y + map->CellHeight - 2 };
    direction = { speed, 0 };
    AnimationBox.y = 0 * AnimationBox.height;
    if ((map->GetCell((pointerTL.x / map->CellWidth) + 1, (pointerTL.y-map->infoBarHeight) / map->CellHeight)->TileType == ROAD) &&
        (map->GetCell((pointerBR.x / map->CellWidth) + 0.01, (pointerBR.y - map->infoBarHeight) / map->CellHeight)->TileType == ROAD)) {
        move();
    }
}
 

void Pacman::goLeft() {
    Vector2 pointerTL = { InitialPosition.x + 1,InitialPosition.y + 2 };
    Vector2 pointerBR = { InitialPosition.x + map->CellWidth - 1,InitialPosition.y + map->CellHeight - 2 };
    direction = {-1 * speed, 0};
    AnimationBox.y = 1 * AnimationBox.height;
    if ((map->GetCell((pointerTL.x / map->CellWidth)-0.01, (pointerTL.y - map->infoBarHeight) / map->CellHeight)->TileType == ROAD) &&
        (map->GetCell((pointerBR.x / map->CellWidth)-1, (pointerBR.y - map->infoBarHeight) / map->CellHeight)->TileType == ROAD)) {
        move();
    }
}

void Pacman::goUp() {
    Vector2 pointerTL = { InitialPosition.x + 1,InitialPosition.y + 2 };
    Vector2 pointerBR = { InitialPosition.x + map->CellWidth - 1,InitialPosition.y + map->CellHeight - 2 };
    direction = {0, -1 * speed};
    AnimationBox.y = 2 * AnimationBox.height;
    if ((map->GetCell(pointerTL.x / map->CellWidth,((pointerTL.y - map->infoBarHeight) / map->CellHeight)-0.01)->TileType == ROAD) &&
        (map->GetCell(pointerBR.x / map->CellWidth,((pointerBR.y - map->infoBarHeight) / map->CellHeight) - 1)->TileType == ROAD)) {
        move();
    }
}

void Pacman::goDown() {
    Vector2 pointerTL = { InitialPosition.x + 1,InitialPosition.y + 2 };
    Vector2 pointerBR = { InitialPosition.x + map->CellWidth - 1,InitialPosition.y + map->CellHeight - 2 };
    direction = {0, speed};
    AnimationBox.y = 3 * AnimationBox.height;
    if ((map->GetCell( pointerTL.x / map->CellWidth, ((pointerTL.y - map->infoBarHeight) / map->CellHeight) + 1)->TileType == ROAD) &&
        (map->GetCell( pointerBR.x / map->CellWidth, ((pointerBR.y - map->infoBarHeight) / map->CellHeight) + 0.01)->TileType == ROAD)) {
        move();
    }
};

void Pacman::setSize() {
    PacmanImage = LoadImage("assets/pac2.png");
    Vector2 OldImageSize = ImageSize;
    ImageSize = {2 * map->CellWidth, 4 * map->CellHeight};
    speed *= (ImageSize.x * ImageSize.y) / (OldImageSize.x * OldImageSize.y);
    ImageResize(&PacmanImage, ImageSize.x, ImageSize.y);
    pacmanText = LoadTextureFromImage(PacmanImage);
    AnimationBox = {0, 0, PacmanImage.width / 2.f, pacmanText.height / 4.f};
    UnloadImage(PacmanImage);
}
