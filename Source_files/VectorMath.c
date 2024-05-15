#include "../Header_files/VectorMath.h"

float ABSf(float a) {
    return a < 0 ? -1 * a : a;
}

Vector2i sumV2i(Vector2i a, Vector2i b) {
    a.x += b.x;
    a.y += b.y;
    return a;
}

Vector2i mulV2i(Vector2i a, Vector2i b) {
    a.x *= b.x;
    a.y *= b.y;
    return a;
}

Vector2i scaleV2i(Vector2i a, int factor) {
    a.x *= factor;
    a.y *= factor;
    return a;
}

Vector2i inverseV2i(Vector2i a) {
    return {
        a.y,
        a.x,
    };
}
