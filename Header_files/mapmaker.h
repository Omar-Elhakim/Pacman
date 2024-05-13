#ifndef MAPMAKER_H
#define MAPMAKER_H
#include "Cell.h"
#include "Map.h"
#include "pacman.h"
#include <raylib.h>

extern int WindowWidth, WindowHeight;
Cell* GetRandomCl();
Vector2i GetRandomCl(Map *map);
void BFS(Vector2i prev[hc][vc], Vector2i from);
void findPath(Vector2i from, Vector2i to);
void makeWall(int x, int y);
void makePath(int x, int y);
bool MouseInBoundries(Vector2 MousePos);
void mapMaker();
void mapMaker(Map *map);
#endif // MAPMAKER_H
