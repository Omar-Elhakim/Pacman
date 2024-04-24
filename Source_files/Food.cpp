#include "../Header_files/Food.h"
#include "raylib.h"

Food::Food(Map* map) {
    count = 0;
    for (int i = 0; i < hc; i++) {
        for (int j = 0; j < vc; j++) {
            if (map->GetCell(j, i)->TileType == ROAD) {
                map->GetCell(j, i)->hasFood = true;
                count++;
            }
            else {
                map->GetCell(j, i)->hasFood = false;
                continue;
            }
        }
    }
}

void Food::draw(Map* map) {
    for (int i = 0; i < hc; i++) {
        for (int j = 0; j < vc; j++) {
            centerx = map->getClPos(map->GetCell(j, i)->arrPos).x + map->CellWidth / 2;
            centery = map->getClPos(map->GetCell(j, i)->arrPos).y + map->CellHeight / 2;
            if (map->GetCell(j, i)->hasFood) {
                DrawCircle(centerx, centery, 5.0f, YELLOW);
            }
            else {
                continue;
            }
        }
    }
}

void Food::update(Map* map) {
    count = 0;
    for (int i = 0; i < hc; i++) {
        for (int j = 0; j < vc; j++) {
            if (map->GetCell(j, i)->TileType == ROAD) {
                map->GetCell(j, i)->hasFood = true;
                count++;
            }
            else {
                map->GetCell(j, i)->hasFood = false;
                continue;
            }
        }
    }
}