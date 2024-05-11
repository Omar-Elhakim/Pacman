#ifndef MAPMAKER_H
#define MAPMAKER_H
#include "Cell.h"
#include "Map.h"
#include "pacman.h"
#include <raylib.h>

extern int WindowWidth, WindowHeight;

void BFS(Vector2 prev[hc][vc], Vector2 from);
void findPath(Vector2 from, Vector2 to);
void makeWall(int x, int y);
void makePath(int x, int y);
bool MouseInBoundries(Vector2 MousePos);
void mapMaker();
void mapMaker(Map *map);
#endif // MAPMAKER_H
