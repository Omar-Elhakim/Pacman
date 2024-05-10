#include <raylib.h>
#include <random>
#include <map>
#include "../Header_files/Map.h"
#include "../Header_files/Ghost.h"
#include "../Header_files/Level.h"
#include "../Header_files/pacman.h"
using namespace std;

Ghost::Ghost(Map* map) :map(map) {
    GhostImage1 = LoadImage("assets/cyanGhost.png");
    GhostImage2 = LoadImage("assets/redGhost.png");
    GhostImage3 = LoadImage("assets/orangeGhost.png");
    GhostImage.push_back(GhostImage1);
    GhostImage.push_back(GhostImage2);
    GhostImage.push_back(GhostImage3);
    imageSize = { 0, 0 };
    speed = 0.0f;
    //map = nullptr;
    imageSize = { 2 * map->CellWidth, 2 * map->CellHeight };
    setSize();
    InitialPosition = map->getClPos(map->GetCell(0, 0)->arrPos);
    Direction = { 0, 0 };

    // UnloadImage(GhostImage);
   // UnloadTexture(ghostText); 
}


void Ghost::setSize() {
    Vector2 OldImageSize = imageSize;
    imageSize = { 2 * map->CellWidth, 4 * map->CellHeight };
    speed *= (imageSize.x * imageSize.y) / (OldImageSize.x * OldImageSize.y);
    for (size_t i = 0; i < 3; i++)
    {
        ImageResize(&GhostImage.at(i), imageSize.x, imageSize.y);
        ghostText[i] = LoadTextureFromImage(GhostImage.at(i));

    }
    for (size_t i = 0; i < 3; i++)
    {
        ghostbox[i] = { 0,0,GhostImage.at(i).width / 8.f,ghostText[i].height / 1.f };
    }
    //UnloadImage(GhostImage);
}


void Ghost::draw() {
    for (size_t i = 0; i < 3; i++)
    {
        DrawTextureRec(ghostText[i], ghostbox[i], InitialPosition, WHITE);
    }
}



void Ghost::move() {
    frameIndex += animationDirection;
    if (frameIndex >= 8 || frameIndex <= 0) {
        animationDirection *= -1;
        frameIndex += animationDirection * 2;
    }
    for (size_t i = 0; i <3; i++)
    {
        ghostbox[i].x = frameIndex * ghostbox[i].width;

    }
    position.x += Direction.x * speed;
    position.y += Direction.y * speed;
}

void Ghost::goRight() {
    for (size_t i = 0; i < 3; i++)
    {
        ghostbox[i].y = 0;
        Direction = { 1, 0 };
        move();
    }
    
}
void Ghost::goLeft() {
    for (size_t i = 0; i < 3; i++) {
        ghostbox[i].y = ghostbox[i].height;
        Direction = { -1, 0 };
        move();
    }
    
}
void Ghost::goUp() {
    for (size_t i = 0; i < 3; i++) {
        ghostbox[i].y = 2 * ghostbox[i].height;
        Direction = { 0, -1 };
        move();
    }
    
}
void Ghost::goDown() {
    for (size_t i = 0; i < 3; i++) {
        ghostbox[i].y = 3 * ghostbox[i].height;
        Direction = { 0, 1 };
        move();
    }
    
}



/*void move(float speed) {
    switch (level) {
    case 1:
        moveRandomly(speed / 2);
        break;
    case 2:
        moveRandomly(speed);
        break;
    case 3:
        moveTowardsPacman();
        break;
    }
}*/
/*
void moveRandomly(float speed) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 3);

    Direction dir = static_cast<Direction>(dis(gen));

    Vector2i change = getDirectionChange(dir);

    if (Map->ispath(position.x + change.x, position.y + change.y)) {
        position.x += change.x * speed;
        position.y += change.y * speed;
        currentDirection = dir;
    }
}

void moveTowardsPacman() {
    Vector2i pacmanPosition = pacman->getPosition();

    std::vector<Vector2i> path = gameMap->FindPath(position, pacmanPosition);

    if (!path.empty()) {
        Vector2i nextStep = path[1];
        position = nextStep;
    }
}

Vector2i getDirectionChange(Direction dir) {
    switch (dir) {
    case goUp:
        return { 0, -1 };
    case goDown:
        return { 0, 1 };
    case goLeft:
        return { -1, 0 };
    case goRight:
        return { 1, 0 };
    default:
        return { 0, 0 };
    }
}
};*/

/*
void Ghost::move(float speed) {
    if (!map) return;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 3);

    static int level = 1;

    if (level == 1) {
        speed /= 2;
        Vector2  randomDirection;
        switch (dis(gen)) {
        case 0:
            randomDirection = { 1, 0 };
            break;
        case 1:
            randomDirection = { -1, 0 };
            break;
        case 2:
            randomDirection = { 0, -1 };
            break;
        case 3:
            randomDirection = { 0, 1 };
            break;
        }

        if (map->isPath(position.x + randomDirection.x * speed, position.y + randomDirection.y * speed)) {
            Direction = randomDirection;
        }
    }
    else if (level == 2) {
        Vector2  randomDirection;
        switch (dis(gen)) {
        case 0:
            randomDirection = { 1, 0 };
            break;
        case 1:
            randomDirection = { -1, 0 };
            break;
        case 2:
            randomDirection = { 0, -1 };
            break;
        case 3:
            randomDirection = { 0, 1 };
            break;
        }

        if (map->isPath(position.x + randomDirection.x * speed, position.y + randomDirection.y * speed)) {
            Direction = randomDirection;
        }
    }
    else if (level == 3) {
        Pacman* pacman;
        if (pacman) {
            Vector2i pacmanPos = map->getClArrPos(pacman->InitialPosition);

            map->FindPath(position, pacmanPos);

            std::vector<Vector2i> path = map->GetCalculatedPath();

            if (!path.empty() && path.size() > 1) {
                Vector2i nextStep = path[1];
                position.x = nextStep.x * map->CellWidth;
                position.y = nextStep.y * map->CellHeight;
            }
        }
    }
    position.x += Direction.x * speed;
    position.y += Direction.y * speed;
}*/