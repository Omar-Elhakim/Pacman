#include "../Header_files/Ghost.h"
#include <raylib.h>
#include "../Header_files/mapmaker.h"
#include "../Header_files/Map.h"
#include "../Header_files/pacman.h"
#include <random>
#include "../Header_files/Cell.h"
using namespace std;
Ghost::Ghost(Map* map) {
 
    position = map->getClPos({1,5});
    color = RED ;
    this->map = map;
}


void Ghost::Draw() {
    DrawRectangle(static_cast<int>(position.x), static_cast<int>(position.y),map->CellWidth, map->CellHeight, color);
}


