#ifndef GHOSTH 
#define GHOSTH 
#include "../Header_files/Map.h"
#include "../Header_files/pacman.h"

class Ghost {
private:
    Image GhostImage1;
    Image GhostImage2;
    Image GhostImage3;
    vector<Image> GhostImage;
    Vector2 imageSize;
    Texture2D  ghostText[4];
    Vector2 InitialPosition;
    Rectangle ghostbox[4];
    int frameIndex;
    float speed;
    int animationDirection;
    Map* map;
public:
    Vector2 position;
    Vector2 Direction;
    Color color;
    // Map* map;
    Ghost(Map* map);
    ~Ghost();
    void draw();
    void setSize();
    void goRight();
    void goLeft();
    void goUp();
    void goDown();
    void move();
    void move(float speed);
    void move(Pacman* pacman);
};
#endif // GHOST_H