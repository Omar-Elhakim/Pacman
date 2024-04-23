#include "../Header_files/food.h"
#include "raylib.h"

void food::drawf() {
    for (int i = 0; i < hc; i++) {
        for (int j = 0; j < vc; j++) {
            centerx = map->getClPos(map->GetCell(j, i)->arrPos).x + map->CellWidth / 2;
            centery = map->getClPos(map->GetCell(j, i)->arrPos).y + map->CellHeight / 2;
            if (map->GetCell(j, i)->TileType != WALL) {
                DrawCircle(centerx, centery, 5.0f, YELLOW);
                fcount++;
            }

            else
                continue;
        }
    }
}
