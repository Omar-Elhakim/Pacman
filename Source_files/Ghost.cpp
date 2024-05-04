#include <raylib.h>
#include <random>
#include <map>
#include "../Header_files/Map.h"
#include "../Header_files/Ghost.h"
#include "../Header_files/Level.h"
#include "../Header_files/pacman.h"
using namespace std;

Ghost::Ghost(Map* map) :map(map) {
    GhostImage = LoadImage("assets/ghost.jpg");
    imageSize = { 0, 0 };
    speed = 0.0f;
    //map = nullptr;
    imageSize = { 2 * map->CellWidth, 2 * map->CellHeight };
    setSize();
    InitialPosition = map->getClPos(map->GetCell(10, 10)->arrPos);
    Direction = { 0, 0 };

    // UnloadImage(GhostImage);
   // UnloadTexture(ghostText); 
}


void Ghost::setSize() {
    GhostImage = LoadImage("assets/ghost.jpg");
    Vector2 OldImageSize = imageSize;
    imageSize = { 2 * map->CellWidth, 4 * map->CellHeight };
    speed *= (imageSize.x * imageSize.y) / (OldImageSize.x * OldImageSize.y);
    ImageResize(&GhostImage, imageSize.x, imageSize.y);
    ghostText = LoadTextureFromImage(GhostImage);
    ghostbox = { 0, 0, GhostImage.width / 8.f, ghostText.height / 1.f};
    UnloadImage(GhostImage);
}


void Ghost::draw() {
    DrawTexture(ghostText, InitialPosition.x, InitialPosition.y, WHITE);
}



void Ghost::move() {
    frameIndex += animationDirection;
    if (frameIndex >= 8 || frameIndex <= 0) { 
        animationDirection *= -1;
        frameIndex += animationDirection * 2;
    }

    ghostbox .x = frameIndex * ghostbox.width;
    position.x += Direction.x * speed; 
    position.y += Direction.y * speed;
}

void Ghost::goRight() {
    ghostbox .y = 0;
    Direction = { 1, 0 };
    move();
}
void Ghost::goLeft() {
    ghostbox .y = ghostbox.height;
    Direction = { -1, 0 };
    move();
}
void Ghost::goUp() {
    ghostbox .y = 2 * ghostbox.height;
    Direction = { 0, -1 };
    move();
}
void Ghost::goDown() {
    ghostbox .y = 3 * ghostbox.height;
    Direction = { 0, 1 };
    move();
}
/*


void move(float speed) {
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
}

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
        /*if (pacman) {
            Vector2i pacmanPos = map->getClArrPos(pacman->InitialPosition);

            map->FindPath(position, pacmanPos); 

            std::vector<Vector2i> path = map->GetCalculatedPath(); 

            if (!path.empty() && path.size() > 1) {
                Vector2i nextStep = path[1]; 
                position.x = nextStep.x * map->CellWidth; 
                position.y = nextStep.y * map->CellHeight;
            }
        }*/
    }
    position.x += Direction.x * speed;
    position.y += Direction.y * speed;
}