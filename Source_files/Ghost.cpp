#include <raylib.h>
#include <random>
#include <map>
#include "../Header_files/Map.h"
#include "../Header_files/Ghost.h"
using namespace std;

Ghost::Ghost(Map* map) :map(map) {
    GhostImage = LoadImage("assets/ghost.jpg");
    imageSize = { 0, 0 };
    speed = 0.0f;
    map = nullptr;
    imageSize = { 2 * map->CellWidth, 2 * map->CellHeight };
    setSize();
    InitialPosition = map->getClPos(map->GetCell(10, 10)->arrPos);
    direction = { 0, 0 };

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
    DrawTexture(ghostText, position.x, position.y, WHITE);
}


void Ghost::move() {
    if (direction.x > 0 && direction.y < 2)
        n++;
    if (n % 9 == 0)
        n = (n + 1) % 3;
        m++;
        if(m>1)
    {
            m = 0; 
    }
        if (direction.x > 1 && direction.y < 4 )
        n++;
        if (n % 9 == 0)
            n = (n + 1) % 3;
        m++;
        if (m > 3)
        {
            m = 2;
        }

        if (direction.y > 3 && direction.x < 6 )
            n++;
        if (n % 9 == 0)
            n = (n + 1) % 3;
        m++;
        if (m > 5)
        {
            m = 4;
        }

        if (direction.y > 5 && direction.x < 7)
            n++;
        if (n % 9 == 0)
            n = (n + 1) % 3;
        m++;
        if (m > 7)
        {
            m = 6;
        }
        ghostbox.x = n * ghostbox.width;
        InitialPosition.x += direction.x;
        InitialPosition.y += direction.y;
}

void Ghost::goRight() {
    ghostbox.y = 0 * ghostbox.height; 
    direction = { speed, 0 };
    move();
}
void Ghost::goLeft() {
    ghostbox.y = 1 * ghostbox.height;
    direction = { -1 * speed, 0 };
    move();
}

void Ghost::goUp() {
    ghostbox.y = 2 * ghostbox.height;
    direction = { 0, -1 * speed };
    move();
}
void Ghost::goDown() {
    ghostbox.y = 3 * ghostbox.height;
    direction = { 0, speed };
    move();
}