#ifndef DifficultyLevelsSH
#define DifficultyLevelsH

#include "Ghost.h"
#include <random>
#include "../Pacman/Header_files/mapmaker.h"
#include "../Pacman/Header_files/Map.h"
#include "../Pacman/Header_files/pacman.h"


class DifficultyLevels {
public:
    static void moveRandomSlowly(Ghost* ghosts[], int , Map* map);
    static void moveRandomQuickly(Ghost* ghosts[], int , Map* map);
    static void moveTowardspacman(Ghost* ghosts[], int , Map* map,Pacman* pacman);
};

#endif
