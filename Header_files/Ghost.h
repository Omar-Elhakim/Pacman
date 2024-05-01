#ifndef GHOSTH 
#define GHOSTH 
#include "../Header_files/Map.h"
#include "../Header_files/pacman.h"

class Ghost {
private:
    Image GhostImage;
    Vector2 imageSize;
    Texture2D  ghostText;
    Vector2 InitialPosition;
    Rectangle ghostbox ;
    int n;
    float speed;
    int m;
Map* map; 
public:
    Vector2i position;
    Vector2 direction;
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