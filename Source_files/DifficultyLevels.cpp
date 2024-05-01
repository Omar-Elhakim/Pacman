#include "../Header_files/DifficultyLevels.h"
#include <raylib.h>
#include "raymath.h"
#include "../Header_files/Map.h"
#include "../Header_files/mapmaker.h"
#include "../Header_files/pacman.h"
#include <random>
#include <queue>



using namespace std;
/*
void DifficultyLevels::moveRandomSlowly(Map *map) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 3);

 for (auto& ghost : map->ghosts) {
        int direction = dis(gen);
        switch (direction) {
        case 0:
            if (map->getClPos map->getClArrPos({ ghost->position.x, ghost->position.y - 1 }) {

            }


            if (!map->IsWall(ghost->position.x, ghost->position.y - 1)) {
                ghost->position.y -= 1;
            }
            break;
        case 1:
            if (!map->IsWall(ghost->position.x, ghost->position.y + 1)) {
                ghost->position.y += 1;
            }
            break;
        case 2:
            if (!map->IsWall(ghost->position.x - 1, ghost->position.y)) {
                ghost->position.x -= 1;
            }
            break;
        case 3:
            if (!map->IsWall(ghost->position.x + 1, ghost->position.y)) {
                ghost->position.x += 1;
            }
            break;
        }
    }
}

void DifficultyLevels::moveRandomQuickly(Map *map) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 3);

    for (auto& ghost : map->ghosts) {
        int direction = dis(gen);
        switch (direction) {
        case 0:
            if (!map->IsWall(ghost->position.x, ghost->position.y - 2)) {
                ghost->position.y -= 2;
            }
            break;
        case 1:
            if (!map->IsWall(ghost->position.x, ghost->position.y + 2)) {
                ghost->position.y += 2;
            }
            break;
        case 2:
            if (!map->IsWall(ghost->position.x - 2, ghost->position.y)) {
                ghost->position.x -= 2;
            }
            break;
        case 3:
            if (!map->IsWall(ghost->position.x + 2, ghost->position.y)) {
                ghost->position.x += 2;
            }
            break;
        }
    }
}



void DifficultyLevels::moveTowardsPlayer(Map *map) {
    std::queue<Vector2> q;
    std::vector<std::vector<int>> visited(map->height, std::vector<int>(map->width, 0));

    for (auto& ghost : map->ghosts) {
        visited.assign(map->height, std::vector<int>(map->width, 0));

        q.push(ghost->position);
        visited[static_cast<int>(ghost->position.y)][static_cast<int>(ghost->position.x)] = 1;

        while (!q.empty()) {
            Vector2 current = q.front();
            q.pop();

            if (map->IsPlayer(current.x, current.y)) {
                break;
            }

            if (!map->IsWall(current.x, current.y - 1) && !visited[static_cast<int>(current.y) - 1][static_cast<int>(current.x)]) {
                q.push({ current.x, current.y - 1 });
                visited[static_cast<int>(current.y) - 1][static_cast<int>(current.x)] = 1;
            }
        }
    }
}*/
/* llllllllllllllllllll
void DifficultyLevels::moveRandomSlowly(Ghost* ghosts[], int numGhosts, Map* map) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 3);

    for (int i = 0; i < numGhosts; ++i) {
        int direction = dis(gen);
        switch (direction) {
        case 0:
            if (map->GetCell(ghosts[i]->position.x, ghosts[i]->position.y - 1)) {
                ghosts[i]->position.y -= 1;
            }
            break;
        case 1:
            if (map->GetCell(ghosts[i]->position.x, ghosts[i]->position.y + 1)) {
                ghosts[i]->position.y += 1;
            }
            break;
        case 2:
            if (map->GetCell(ghosts[i]->position.x - 1, ghosts[i]->position.y)) {
                ghosts[i]->position.x -= 1;
            }
            break;
        case 3:
            if (map->GetCell(ghosts[i]->position.x + 1, ghosts[i]->position.y)) {
                ghosts[i]->position.x += 1;
            }
            break;
        }
    }
}

void DifficultyLevels::moveRandomQuickly(Ghost* ghosts[], int numGhosts, Map* map) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 3);

    for (int i = 0; i < numGhosts; ++i) {
        int direction = dis(gen);
        switch (direction) {
        case 0:
            if (map->GetCell(ghosts[i]->position.x, ghosts[i]->position.y - 2)) {
                ghosts[i]->position.y -= 2;
            }
            break;
        case 1:
            if (map->GetCell(ghosts[i]->position.x, ghosts[i]->position.y + 2)) {
                ghosts[i]->position.y += 2;
            }
            break;
        case 2:
            if (map->GetCell(ghosts[i]->position.x - 2, ghosts[i]->position.y)) {
                ghosts[i]->position.x -= 2;
            }
            break;
        case 3:
            if (map->GetCell(ghosts[i]->position.x + 2, ghosts[i]->position.y)) {
                ghosts[i]->position.x += 2;
            }
            break;
        }
    }
}

void DifficultyLevels::moveTowardspacman(Ghost* ghosts[], int numGhosts, Map* map, Pacman* pacman) {

    Vector2i playerPos = map->getClArrPos(pacman->InitialPosition);
    Vector2i nearestGhostPos;
    float minDistance = std::numeric_limits<float>::max();

    for (int i = 0; i < numGhosts; ++i) {
        float distance = Vector2Distance(pacman->InitialPosition, ghosts[i]->position);
        if (distance < minDistance) {
            minDistance = distance;
            nearestGhostPos = map->getClArrPos(ghosts[i]->position);
        }
    }

    map->FindPath(nearestGhostPos, playerPos);
}
*/