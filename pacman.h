#pragma once
#include "raylib.h"
#include <cmath>
class pacman
{
public:
	pacman();
    Image pac ;
    Texture2D pacman1 ;
    Rectangle box;
    Vector2 position;
    Vector2 direction ;
    float speed ;
    float x ;
    int a ;
    void f();
	static void funco(Texture2D pacman1, Vector2 position, Vector2 direction, Rectangle box, Image pac, float speed,float x, int a );
	static void moveright(Vector2 p,Vector2 d,Rectangle r, Image pacman,float speed, float x, int a);
	static void moveleft(Vector2 p, Vector2 d, Rectangle r, Image pacman, float speed, float x, int a);
	static void moveup(Vector2 p, Vector2 d, Rectangle r, Image pacman, float speed, float x, int a);
	static void movedown(Vector2 p, Vector2 d, Rectangle r, Image pacman, float speed, float x, int a);
};

