#pragma once
#include "Cell.h"
#include <raylib.h>

float ABSf(float a);
int ABSi(int a);

Vector2i sumV2i(Vector2i a, Vector2i b);
Vector2i mulV2i(Vector2i a, Vector2i b);
Vector2i scaleV2i(Vector2i a, int factor);
Vector2i inverseV2i(Vector2i a);
Vector2i V2toV2i(Vector2 a);

Vector2 sumV2(Vector2 a, Vector2 b);
Vector2 mulV2(Vector2 a, Vector2 b);
Vector2 scaleV2(Vector2 a, float factor);
Vector2 inverseV2(Vector2 a);
Vector2 V2itoV2(Vector2i a);
