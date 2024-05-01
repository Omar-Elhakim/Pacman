#ifndef DifficultyLevels_H
#define DifficultyLevels_H

#include "Ghost.h"
#include <random>
#include "mapmaker.h"
#include "Map.h"
#include "pacman.h"


class DifficultyLevels {
public:
    static void moveRandomSlowly(Ghost* ghosts[], int , Map* map);
    static void moveRandomQuickly(Ghost* ghosts[], int , Map* map);
    static void moveTowardspacman(Ghost* ghosts[], int , Map* map,Pacman* pacman);
};

#endif
