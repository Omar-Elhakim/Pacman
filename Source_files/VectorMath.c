#include "../Header_files/VectorMath.h"

float ABSf(float a) {
    return a < 0 ? -1 * a : a;
}

int ABSi(int a) {
    return a < 0 ? -1 * a : a;
}

Vector2i sumV2i(Vector2i a, Vector2i b) {
    Vector2i t = {
        a.x + b.x,
        a.y + b.y,
    };
    return t;
}

Vector2i mulV2i(Vector2i a, Vector2i b) {
    Vector2i t = {
        a.x * b.x,
        a.y * b.y,
    };
    return t;
}

Vector2i scaleV2i(Vector2i a, int factor) {
    Vector2i t = {
        a.x * factor,
        a.y * factor,
    };
    return t;
}

Vector2i inverseV2i(Vector2i a) {
    Vector2i t = {
        a.y,
        a.x,
    };
    return t;
}

Vector2i V2toV2i(Vector2 a) {
    Vector2i t = {
        (int)a.x,
        (int)a.y,
    };
    return t;
}

Vector2 sumV2(Vector2 a, Vector2 b) {
    Vector2 t = {
        a.x + b.x,
        a.y + b.y,
    };
    return t;
}

Vector2 mulV2(Vector2 a, Vector2 b) {
    Vector2 t = {
        a.x * b.x,
        a.y * b.y,
    };
    return t;
}

Vector2 scaleV2(Vector2 a, float factor) {
    Vector2 t = {
        a.x * factor,
        a.y * factor,
    };
    return t;
}

Vector2 inverseV2(Vector2 a) {
    Vector2 t = {
        a.y,
        a.x,
    };
    return t;
}

Vector2 V2itoV2(Vector2i a) {
    Vector2 t = {
        (float)a.x,
        (float)a.y,
    };
    return t;
}
