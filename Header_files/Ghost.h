#ifndef GHOSTH
#define GHOSTH

#include <raylib.h>
#include "mapmaker.h"
#include "Map.h"
#include "pacman.h"
#include "Ghost.h"
#include <random>
class Ghost {
public:
    Vector2 position;
    Color color;
    Map* map;
   void move(float speed);
   void move(Pacman* pacman);

    Ghost(Map* map);

    void Draw();
};

#endif // GHOST_H
