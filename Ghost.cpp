#include "Ghost.h"
#include <raylib.h>
#include "../Pacman/Header_files/mapmaker.h"
#include "../Pacman/Header_files/Map.h"
#include "../Pacman/Header_files/pacman.h"
#include <random>
#include "Header_files/Cell.h"
using namespace std;
Ghost::Ghost(Map* map) {
 
    position = map->getClPos({1,5});
    color = RED ;
    this->map = map;
}


void Ghost::Draw() {
    DrawRectangle(static_cast<int>(position.x), static_cast<int>(position.y),map->CellWidth, map->CellHeight, color);
}


