#ifndef GHOSTH 
#define GHOSTH 
#include "../Header_files/Map.h"
#include "../Header_files/pacman.h"

class Ghost {
private:
    Image ghostImages[4];
    Vector2 imageSize;
    Texture2D  ghostText[4];
    Rectangle ghostbox[4];
    int frameIndex;
    float speed;
    int animationDirection;
    int a;
    int x;
    Map* map;
public:
    Vector2 InitialPosition[4];
    Vector2 Direction;
    Color color;
    // Map* map;
    Ghost(Map* map);
    ~Ghost();
    Vector2 GenerateRandomDirection();
    void draw();
    void setSize();
    void goRight();
    void goLeft();
    void goUp();
    void goDown();
    void move();
    void moveto(vector<Vector2> path ,int ghostindex);
    void moveRandomly(float);
};
#endif // GHOST_H